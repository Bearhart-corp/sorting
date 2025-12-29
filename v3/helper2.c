/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <tbelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 13:09:37 by tbelard           #+#    #+#             */
/*   Updated: 2025/12/28 17:08:09 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	algo_3move(t_meta *ssa, t_stack *a)
{
	if (a[ssa->head].val > a[a[ssa->head].next].val
		&& a[ssa->head].val > a[a[a[ssa->head].next].next].val)
	{
		ra(ssa, a);
		ssa->count++;
	}
	else if (a[a[ssa->head].next].val >
		a[a[a[ssa->head].next].next].val)
	{
		rra(ssa, a);
		ssa->count++;
	}
	if (a[ssa->head].val > a[a[ssa->head].next].val)
	{
		sa(ssa, a);	
		ssa->count++;
	}
}

void	init(int n_elem, t_stack *a, t_stack *b)
{
	int i;
	int	j;

	i = MAX_NBR - 1;
	j = 0;
	a[i].next = MAX_NBR - n_elem;
	while (--n_elem)
	{
		a[i--].prev = (MAX_NBR - 2 - j);
		a[i].next = ((MAX_NBR - 1 - j) % MAX_NBR);
		j++;
	}
	a[i].next = MAX_NBR - j;
	a[i].prev = MAX_NBR - 1; //on le fait pointer vers le dernier
	i = 0;
	while (i < n_elem)
		b[i++].val = 0;
}

void	init_meta_data(t_meta *ssa, t_meta *ssb, int n_elem)
{
	ssa->size = (size_t)n_elem;
	ssb->size = 0;
	ssa->head = (size_t)(MAX_NBR - n_elem);
	ssb->head = (size_t)MAX_NBR - 1;
	ssa->ifree = MAX_NBR;
	ssb->ifree = 0;	
	while (ssb->ifree < MAX_NBR)
	{
		ssb->free[ssb->ifree] = ssb->ifree;
		ssb->ifree++;
	}
	ssb->ifree = 0;
}

void	ft_push_swap(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	if (ssa->size < 4)
	{
		algo_3move(ssa, a);
		ssa->start_l = ssa->head;
	}
	else
	{
		ft_print_stack(*ssa, *ssb, a, b);
		vingt_pour_100(ssa, ssb, a, b);
		//cocktail(ssa, ssb, a, b);
	}
	ssa->start_l = ssa->head;
	printf("\n\tcost: %zu\n", ssa->count);
	ft_print_stack(*ssa, *ssb, a, b);
}