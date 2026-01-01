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


int smallest_bigger() =

	value = 0xffffffff;
	flag = 0;
	while (ssa.size-- > 0)
	{
		if (a[ssa.head].val > b[ssb.head].val)
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
*/

int	find_biggest_smaller_inB(t_meta ssa, t_meta ssb, t_stack *a, t_stack *b)
{
	uint32_t 	value;
	char		flag;

	value = 0;
	flag = 0;
	while (ssb.size-- > 0)
	{
		if (b[ssb.head].val < a[ssa.head].val)
		{
			if (b[ssb.head].val > value)
				value = b[ssb.head].val;
			flag = 1;
		}
		ssb.head = b[ssb.head].next;
	}
	if (flag == 0)
		value = 0;
	return (value);
}

int	prev_or_next(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	size_t	nexta;
	size_t	preva;
	size_t	nextb;
	size_t	prevb;

	nexta = a[ssa->head].next;
	preva = a[ssa->head].prev;
	nextb = b[ssb->head].next;
	prevb = b[ssb->head].prev;
	if (a[nexta].val < a[ssa->head].val && a[nexta].val < a[preva].val
		&& b[nextb].val > b[ssb->head].val && b[nextb].val > b[prevb].val)
		return (rr(ssa, ssb, a, b));
	if (a[nexta].val < a[ssa->head].val && a[nexta].val < a[preva].val)
		return (ra(ssa, a));
	if (b[nextb].val > b[ssb->head].val && b[nextb].val > b[prevb].val)
		return (rb(ssb, b));
	if (a[preva].val < a[ssa->head].val && a[preva].val < a[nexta].val
		&& b[prevb].val > b[ssb->head].val && b[prevb].val > b[nextb].val)
		return (rrr(ssa, ssb, a, b));
	if (a[preva].val < a[ssa->head].val && a[preva].val < a[nexta].val)
		return (rra(ssa, a));
	if (b[prevb].val > b[ssb->head].val && b[prevb].val > b[nextb].val)
		return (rrb(ssb, b));
	return (0);
}

void quick_turk(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	char	bol;
	char	bol_b;

	while (ssa->size > 3)
		quick_2(ssa, ssb, a, b);
	algo_2move(ssa, a);

	while (ssb->size)
	{
		ssa->target = ssa->n - ssa->size;
		ssb->target = ssa->target - 1;
		ssa->flag = 'b';
		bol = up_or_down(*ssa, *ssb, a, b);
		while (b[ssb->head].val != ssb->target)
		{
			if (bol)
				ssa->count += rrb(ssb, b);
			else
				ssa->count += rb(ssb, b);
		}
		ssa->count += pa(ssa, ssb, a, b);
	}
}

//8k op pour 500, 2k pour 250 et 590 pour 100
/* 
si en chemin tu trouve le numero en cours + 1 tu le push quand meme et ensuite tu
swap sur b si besoin

276 == 285


deuxieme algo plus complexe et moins efficiant
	while (ssb->size)
	{
		ssa->count += prev_or_next(ssa, ssb, a,b);
		ssa->target = find_smallest_bigger_inA(*ssa, *ssb, a, b);
		ssa->flag = 'a';
		bol = up_or_down(*ssa, *ssb, a, b);
		while (a[ssa->head].val != ssa->target)
		{
			if (bol)
				ssa->count += rra(ssa, a);
			else
				ssa->count += ra(ssa, a);
		}
		ssa->count += pa(ssa, ssb, a, b);
	}

troisieme algo entre 2 :

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
*/