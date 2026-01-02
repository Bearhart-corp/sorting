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

void	algo_2move(t_meta *ssa, t_stack *a)
{
	if (a[ssa->head].val > a[a[ssa->head].next].val
		&& a[ssa->head].val > a[a[a[ssa->head].next].next].val)
		ssa->count += ra(ssa, a);
	else if (a[a[ssa->head].next].val > a[a[a[ssa->head].next].next].val)
		ssa->count += rra(ssa, a);
	if (a[ssa->head].val > a[a[ssa->head].next].val)
		ssa->count += sa(ssa, a);	
}

int	find_smallest_bigger_inA(t_meta ssa, t_meta ssb, t_stack *a, t_stack *b)
{
	uint32_t 	value;
	char		flag;

	value = 0xffffffff;
	flag = 0;
	while (ssa.size-- > 0)
	{
		if (a[ssa.head].val > ssb.target)
		{
			if (a[ssa.head].val < value)
				value = a[ssa.head].val;
			flag = 1;
		}
		ssa.head = a[ssa.head].next;
	}
	if (flag == 0)
		value = 0;
	return (value);
}