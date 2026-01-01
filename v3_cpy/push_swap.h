/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <tbelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 13:10:00 by tbelard           #+#    #+#             */
/*   Updated: 2025/12/28 17:06:34 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# ifndef MAX_NBR
#  define MAX_NBR 0x200 //max (4095)
# endif

typedef struct s_meta
{
	size_t		size;
	size_t		n;
	size_t		i;
	size_t		target;
	size_t		head;
	size_t		count;
	size_t		odd;
	size_t		top_phys;
	size_t		start_l;
	size_t		end_l;
	uint16_t	free[MAX_NBR];
	size_t		ifree;
	char		flag;
	char		double_op;
}	t_meta;

typedef struct s_stack
{
	int32_t	val;
	int16_t	prev;
	int16_t	next;
}	t_stack;

typedef struct s_main
{
	int 	i;
	int 	j;
	int		t;
	long	sentinel;
	int 	count;
	char	seen[MAX_NBR];
}	t_main;

///////// helper classik
void	init(int n_elem, t_stack *a, t_stack *b);
void	init_meta_data(t_meta *ssa, t_meta *ssb, int n_elem);
void	ft_print_stack(t_meta ssa, t_meta ssb, t_stack *a, t_stack *b);
long	ft_atoi(char **s_ptr, char *s, int base);
int		ft_still_number(char *s);
/////////
int		find_smallest_bigger_inA(t_meta ssa, t_meta ssb, t_stack *a, t_stack *b);
float	desorder(t_meta ssa, t_meta ssb, t_stack *a, t_stack *b);
int		isNot_sorted(t_meta ssa, t_meta ssb, t_stack *a, t_stack *b);
char	up_or_down(t_meta ssa, t_meta ssb, t_stack *a, t_stack *b);
//warning need ssa->flag = 'a' ou 'b';

///////// stack helper
size_t	pb(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b);
size_t	pa(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b);
size_t	ss(t_meta *ssa, t_meta *ssb, t_stack *b, t_stack *a);
size_t	sb(t_meta *ssb, t_stack *b);
size_t	sa(t_meta *ssa, t_stack *a);
size_t	rr(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b);
size_t	rrr(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b);
size_t	rrb(t_meta *ssb, t_stack *b);
size_t	rb(t_meta *ssb, t_stack *b);
size_t	rra(t_meta *ssa, t_stack *a);
size_t	ra(t_meta *ssa, t_stack *a);
/////////

///////// algo de tri
void	insertion(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b);
void	cocktail(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b);
void	algo_2move(t_meta *ssa, t_stack *a);
void	ft_push_swap(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b);
void 	quick_turk(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b);

#endif