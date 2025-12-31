/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_turk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 11:46:44 by tbelard           #+#    #+#             */
/*   Updated: 2025/12/31 11:46:46 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	quick_2(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	int		i;
	short	median;

	i = ssa->size;
	median = ssa->n - (i / 2);
	while (ssa->size > (i / 2))
	{
		if (a[ssa->head].val < median)
		{
			ssa->count += pb(ssa, ssb, a, b);
			if (b[ssb->head].val < (i / 4 + (ssa->n - i)))
				ssa->count += rb(ssb, b);
		}
		else
			ssa->count += ra(ssa, a);
	}
}

void quick_turk(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	char	bol;
	//on push 50 % recurssivement jusquau cas de base ssa->size < 3
		//pivot de 50% sur B
	while (ssa->size > 3)
		quick_2(ssa, ssb, a, b);
	// algo deterministe pour 3 elements
	algo_2move(ssa, a);
	//smallest bigger insersion sur A
		//analyse le ssb.head et le b[ssb.head].prev puis pa ou rrb/rrr et pa
	while (ssb->size)
	{
		if (b[ssb->head].val < b[b[ssb->head].prev].val)
			ssa->count += rrb(ssb, b);
		ssa->target = find_smallest_bigger_inA(*ssa, *ssb, a, b);
		ssa->flag = 'a';
		bol = up_or_down(*ssa, *ssb, a, b); // si 1 alors rra
		while (a[ssa->head].val != ssa->target)
		{
			if (bol)
				ssa->count += rra(ssa, a);
			else
				ssa->count += ra(ssa, a);
		}
		ssa->count += pa(ssa, ssb, a, b);
	}
	//opti avec choix de rr ou rrr

	//opti avec des swaps si plus rentable
}

