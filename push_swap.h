/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 13:10:00 by tbelard           #+#    #+#             */
/*   Updated: 2025/12/14 13:10:03 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# define MAX_NUMBER_TO_SORT 0x200
# define INDEX_PREV 0xa
# define MASK 0x3ff
# define VALUE 0x14
# define CTRL 0x1e
# define IN_A 1
# define IN_B 2
# define FREE 0

typedef struct s_meta
{
	size_t		size;
	size_t		head;
	size_t		cap;
	uint16_t	free_lst[0x800]; //cap max 2047
	size_t		ifree;
}	t_meta;

///////// helper classik
void	*ft_memcpy(void *dest, const void *src, size_t n_byte);
void	init(int n_elem, int *a);
/////////

///////// stack helper
void	pb(t_meta sa, t_meta sb, int *a, int *b);
void	pa(t_meta *sa, t_meta *sb, int *a, int *b);
void	ss(t_meta sa, t_meta sb, int *b, int *a);
void	sb(t_meta sb, int *b);
void	sa(t_meta sa, int *a);
void	rr(t_meta sa, t_meta sb, int *a, int *b);
void	rrr(t_meta sa, t_meta sb, int *a, int *b);
void	rrb(t_meta sb, int *b);
void	rb(t_meta sb, int *b);
void	rra(t_meta sa, int *a);
void	ra(t_meta sa, int *a);
/////////

#endif
