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
			{
				if (a[ssa->head].val >= median)
					ssa->count += rr(ssa, ssb, a, b);
				else
					ssa->count += rb(ssb, b);
			}
		}
		else
			ssa->count += ra(ssa, a);
	}
}
/*

char	up_or_down(t_meta ssa, t_meta ssb, t_stack *a, t_stack *b)
{
	short	count;

	if (ssa.flag == 'a')
	{
		while (a[ssa.head].val != ssa.target)
		{
			count++;
			ssa.head = a[ssa.head].next;
		}
		return (count >= (ssa.size / 2));//rra = 1
	}
	else
	{
		while (b[ssb.head].val != ssa.target)
		{
			count++;
			ssb.head = b[ssb.head].next;
		}
		return (count >= (ssb.size / 2));
	}
}
*/

int	find_biggest_smaller_inB(t_meta ssa, t_meta ssb, t_stack *a, t_stack *b)
{
	uint32_t 	value;
	char		flag;

	value = 0xffffffff;
	flag = 0;
	while (ssb.size-- > 0)
	{
		if (b[ssb.head].val > a[ssa.head].val)
		{
			if (b[ssb.head].val < value)
				value = b[ssb.head].val;
			flag = 1;
		}
		ssb.head = b[ssb.head].next;
	}
	if (flag == 0)
		value = 0;
	return (value);
}

void quick_turk(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	char	bol;
	char	bol_b;

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
		{
			if(a[ssa->head].val > a[a[ssa->head].prev].val)
				ssa->count += rrr(ssa, ssb, a, b);
			else
				ssa->count += rrb(ssb, b);
		}
		ssa->target = find_smallest_bigger_inA(*ssa, *ssb, a, b);
		//ssb->target = find_biggest_smaller_inB(*ssa, *ssb, a, b);
		ssa->flag = 'a';
		bol = up_or_down(*ssa, *ssb, a, b);
		//ssa->flag = 'b';
		//bol_b = up_or_down(*ssa, *ssb, a, b);
		while (a[ssa->head].val != ssa->target)
		{
			if (bol)
			{
				ssa->count += rra(ssa, a);
			}
			else
				ssa->count += ra(ssa, a);
		}
		ssa->count += pa(ssa, ssb, a, b);
	}
	//opti avec choix de rr ou rrr

	//opti avec des swaps si plus rentable
}

/* 
si en chemin tu trouve le numero en cours + 1 tu le push quand meme et ensuite tu
swap sur b si besoin

276 == 285
*/