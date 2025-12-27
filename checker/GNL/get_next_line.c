/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaboure <etaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:03:30 by etaboure          #+#    #+#             */
/*   Updated: 2025/12/27 14:59:25 by etaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_line(char *buf, t_arg *s, int fd)
{
	if (buf[0] != 0)
		return (1);
	s->state = read(fd, buf, BUFFER_SIZE);
	if (s->state <= 0 || !buf)
		return (0);
	buf[s->state] = 0;
	return (1);
}

static int	get_buf(char *buf, t_arg *s)
{
	while (buf[s->index] && buf[s->index] != '\n')
		s->index++;
	if (s->index == (size_t)s->state)
	{
		ft_memmove(s->line + s->l_size, buf, s->index);
		s->l_size += s->index;
		s->line[s->l_size] = 0;
		s->index = 0;
		buf[0] = 0;
		return (1);
	}
	ft_memmove(s->line + s->l_size, buf, s->index + 1);
	s->l_size += s->index + 1;
	s->line[s->l_size] = 0;
	s->state -= s->index + 1;
	ft_memmove(buf, buf + s->index + 1, s->state);
	buf[s->state] = 0;
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buf[OPEN_MAX][BUFFER_SIZE + 1] = {0};
	t_arg		s;
	int			i;

	if (fd < 0 || fd == 1 || fd == 2 || BUFFER_SIZE <= 0
		|| read(fd, buf[fd], 0) < 0)
		return (NULL);
	if (!ft_init(&s, buf[fd]))
		return (NULL);
	while (1)
	{
		if (!read_line(buf[fd], &s, fd))
			break ;
		i = get_buf(buf[fd], &s);
		if (i == 1)
			s.line = ft_realloc(s.line, &s);
		if (i == 0)
			return (s.line);
	}
	if (s.l_size == 0)
		return (free(s.line), NULL);
	s.line[s.l_size] = 0;
	return (s.line);
}
