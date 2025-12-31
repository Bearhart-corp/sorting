/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_pourcent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 15:10:11 by tbelard           #+#    #+#             */
/*   Updated: 2025/12/29 15:10:13 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	insertion(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	int i;

	i = 0;
	while (ssa->size)
	{
		ssa->flag = 'a';
		ssa->target = i++;
		ssa->flag = up_or_down(*ssa, *ssb, a, b);
		while (a[ssa->head].val != ssa->target)
		{
			if (ssa->flag)
				ssa->count += rra(ssa, a);
			else
				ssa->count += ra(ssa, a);
		}
		ssa->count += pb(ssa, ssb, a, b);
	}
	ssa->flag = 'b';
	ssa->target = 0;
	ssa->flag = up_or_down(*ssa, *ssb, a, b);
	while (b[ssb->head].val != 0)
	{
		if (ssa->flag)
			ssa->count += rrb(ssb, b);
		else
			ssa->count += rb(ssb, b);
	}
	ssa->count += rb(ssb, b);
		while (ssb->size)
			ssa->count += pa(ssa, ssb, a, b);
}