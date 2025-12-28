/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 14:46:13 by tbelard           #+#    #+#             */
/*   Updated: 2025/12/28 14:46:15 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	isNot_sorted(t_meta ssa, t_meta ssb, t_stack *a, t_stack *b)
{
	int i;

	i = 0;
	while (ssa.size-- > 1)
	{
		if (a[ssa.top_phys].val > a[a[ssa.top_phys].next].val)
			i = 1;
		ssa.top_phys = a[ssa.top_phys].next;
	}
	while (ssb.size-- > 1)
	{
		if (b[ssb.top_phys].val < b[b[ssb.top_phys].next].val)
			i = 1;
		ssb.top_phys = b[ssb.top_phys].next;
	}
	return (i); //0 = is sorted
}

void	ft_print_stack(t_meta ssa, t_meta ssb, t_stack *a, t_stack *b)
{
	printf("\n\tETAT STACK A\n\n");
	ssa.head = ssa.start_l;
	ssb.head = ssb.start_l;
	for(int p = 0; p < ssa.size; p++)
	{
		printf("\t[%zu]", ssa.head);
		printf("\t= %d\n" , a[ssa.head].val);
		ssa.head = a[ssa.head].next;
	}
	printf("\n\tETAT STACK B\n\n");
	for(int p = 0; p < ssb.size; p++)
	{
		printf("\t[%zu]", ssb.head);
		printf("\t= %d\n" , b[ssb.head].val);
		ssb.head = b[ssb.head].next;
	}
}