/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaboure <etaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:06:33 by etaboure          #+#    #+#             */
/*   Updated: 2025/12/27 14:59:33 by etaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
# define OPEN_MAX 1024

/*main*/
char	*get_next_line(int fd);

/*utils*/
typedef struct s_arg
{
	char	*line;
	size_t	capa;
	ssize_t	state;
	size_t	index;
	size_t	l_size;
}	t_arg;
int		ft_init(t_arg *s, char *buf);
char	*ft_realloc(char *src, t_arg *s);
void	*ft_memmove(void *dest, const void *src, size_t n);

#endif