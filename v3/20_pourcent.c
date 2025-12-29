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

float	desorder(t_meta ssa, t_meta ssb, t_stack *a, t_stack *b)
{
	float 	mistake;
	float	total_pairs;
	int		i;
	int		j;

	i = ssa.head;
	ssa.end_l = a[i].prev;
	mistake = 0;
	total_pairs = 0;
	while (i != ssa.end_l)
	{
		j = a[i].next;
		while (j != ssa.end_l)
		{
			total_pairs++;
			if (a[i].val > a[j].val)
				mistake++;
			j = a[j].next;
		}
		i = a[i].next;
	}
	return (((mistake / total_pairs)));
}

static char	up_or_down(t_meta ssa, t_meta ssb, t_stack *a, t_stack *b)
{
	short	count;

	if (ssa.flag == 'a')
	{
		while (a[ssa.head].val != ssa.target)
		{
			count++;
			ssa.head = a[ssa.head].next;
		}
		if (count >= ssa.size / 2)
			return (1);
	}
	else
	{
		while (b[ssb.head].val != ssa.target)
		{
			count++;
			ssb.head = b[ssb.head].next;
		}
		if (count >= ssb.size / 2)
			return (1);
	}
	return (0);
}

void	vingt_pour_100(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	char	direction;

	ssa->count = 0;
	ssa->start_l = ssa->head;
	ssa->end_l = a[ssa->head].prev;
	printf("end : %zu\n",ssa->end_l );
	printf("dis:%.10f\n", desorder(*ssa, *ssb, a, b));
	while (ssa->head != ssa->end_l && desorder(*ssa, *ssb, a, b) != 0)
	{
		if (a[ssa->head].val > a[a[ssa->head].next].val)
		{
			ssa->count += pb(ssa, ssb, a, b);
		}
		else
			ssa->count += ra(ssa, a);
	}
	ra(ssa, a);
	//ssa->head = ssa->start_l;
	ft_print_stack(*ssa, *ssb, a, b);

	printf("dis:%.10f\n", desorder(*ssa, *ssb, a, b));
}
