/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaboure <etaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:08:25 by etaboure          #+#    #+#             */
/*   Updated: 2025/12/27 14:59:20 by etaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_init(t_arg *s, char *buf)
{
	s->capa = BUFFER_SIZE + 1;
	s->state = 0;
	s->line = malloc(s->capa);
	if (!s->line)
		return (0);
	while (buf[s->state])
		s->state++;
	s->index = 0;
	s->l_size = 0;
	return (1);
}

char	*ft_realloc(char *src, t_arg *s)
{
	char	*ptr;

	if (s->capa - s->l_size >= BUFFER_SIZE + 1)
		return (src);
	s->capa = s->capa << 1;
	ptr = src;
	src = malloc(s->capa);
	if (!src)
		return (NULL);
	ft_memmove(src, ptr, s->l_size);
	free(ptr);
	return (src);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!n || dest == src)
		return (dest);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d < s)
		while (n--)
			*d++ = *s++;
	else
		while (n--)
			d[n] = s[n];
	return (dest);
}
