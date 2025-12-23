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

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# ifndef MAX_NBR
#  define MAX_NBR 0x200
# endif

typedef struct s_meta
{
	size_t		size;
	size_t		head;
	size_t		start;
	size_t		start_l;
	size_t		end_l;
	uint16_t	free[MAX_NBR];
	size_t		ifree;
}	t_meta;

typedef struct s_stack
{
	int32_t	val;
	int16_t	prev;
	int16_t	next;
}	t_stack;

///////// helper classik
void	init(int n_elem, t_stack *a, t_stack *b);
void	init_meta_data(t_meta *ssa, t_meta *ssb, int n_elem);
void	ft_print_stack(t_meta ssa, t_meta ssb, t_stack *a, t_stack *b);
/////////

///////// stack helper
void	pb(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b);
void	pa(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b);
void	ss(t_meta *ssa, t_meta *ssb, t_stack *b, t_stack *a);
void	sb(t_meta *ssb, t_stack *b);
void	sa(t_meta *ssa, t_stack *a);
void	rr(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b);
void	rrr(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b);
void	rrb(t_meta *ssb, t_stack *b);
void	rb(t_meta *ssb, t_stack *b);
void	rra(t_meta *ssa, t_stack *a);
void	ra(t_meta *ssa, t_stack *a);
/////////
void	ft_push_swap(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b);
void	algo_3move(t_meta *ssa, t_stack *a);

#endif
