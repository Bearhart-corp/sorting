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

int	maxB(t_meta ssb, t_stack *b, size_t *target)
{
	size_t	count;
	size_t	size;
	int		max_count;

	count = 0;
	size = ssb.size;
	*target = b[ssb.head].val;
	while (ssb.size--)
	{
		if (b[ssb.head].val > *target)
		{
			max_count = count;
			*target = b[ssb.head].val;
		}
		ssb.head = b[ssb.head].next;
		count++;
	}
	if (max_count > (int)(size / 2))
		return (max_count - size);
	return (max_count);
}

int	up_or_down(t_meta ssa, t_meta ssb, t_stack *a, t_stack *b)
{
	int	count;

	count = 0;
	while (a[ssa.head].val != ssa.target)
	{
		count++;
		ssa.head = a[ssa.head].next;
	}
	if (count > ssa.size / 2)
		return (count - ssa.size);
	return (count);
}

void quick_turk(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	int bol;
	int bol_b;
	int i;
	int j;

	while (ssa->size > 3)
		quick_2(ssa, ssb, a, b);
	algo_2move(ssa, a);
	
	while (ssb->size)
	{
		i = 0;
		if (b[ssb->head].val < b[b[ssb->head].prev].val)//test en while
			ssa->count += rrb(ssb, b);
		while (b[ssb->head].val < a[ssa->head].val)
		{
			ssa->count += pa(ssa, ssb, a, b);
			i++;
		}
		j = i;
		while (i--)
			rra(ssa, a);
		ssa->count += pa(ssa, ssb, a, b);

		while (j--)
			ra(ssa, a);
	}
}

/*
I = 0
while que valeur top B ou bottom B < top A
	push a
while top B ou bottom B > top A
	ra
	I++
while que valeur (B < top A) & (B > bottom A) & i > 0
	push a
while bottom A > top or bottom B & I--
	rra



si chunk >= 250 on refait un quick sort

//8k op pour 500, 2k pour 250 et 590 pour 100

276 == 285


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


	ALGO 4:

	i = 1;
		bol_b = maxB(*ssb, b, &ssb->target);
		ssa->target = ssb->target + 1;
		ssa->flag = 'a';
		bol = up_or_down(*ssa, *ssb, a, b);
		while (a[ssa->head].val != ssa->target
			|| b[ssb->head].val != ssb->target)
		{
			if (b[ssb->head].val == ssb->target - i)
			{
				ssa->count += pa(ssa, ssb, a, b);
				//bol_b = maxB(*ssb, b, &ssb->target);
				ssa->flag = 'a';
				bol = up_or_down(*ssa, *ssb, a, b);
				i++;
			}
			else
			{
				if (bol < 0 && bol_b < 0)
				{
					if (b[ssb->head].val != ssb->target
						&& a[ssa->head].val != ssa->target)
						ssa->count += rrr(ssa, ssb, a, b);
					else if (a[ssa->head].val != ssa->target)
						ssa->count += rra(ssa, a);
					else if (b[ssb->head].val != ssb->target)
						ssa->count += rrb(ssb, b);
				}
				else if (bol < 0)
				{
					if (a[ssa->head].val != ssa->target)
						ssa->count += rra(ssa, a);
					if (b[ssb->head].val != ssb->target)
						ssa->count += rb(ssb, b);
				}
				else if (bol_b < 0)
				{
					if (a[ssa->head].val != ssa->target)
						ssa->count += ra(ssa, a);
					if (b[ssb->head].val != ssb->target)
						ssa->count += rrb(ssb, b);
				}
				else
				{
					if (b[ssb->head].val != ssb->target
						&& a[ssa->head].val != ssa->target)
						ssa->count += rr(ssa, ssb, a, b);
					else if (a[ssa->head].val != ssa->target)
						ssa->count += ra(ssa, a);
					else if (b[ssb->head].val != ssb->target)
						ssa->count += rb(ssb, b);
				}
			}
		}
		j = i;
		while(i-- > 1)
			ssa->count += ra(ssa, a);
		ssa->count += pa(ssa, ssb, a, b);
		while(j-- > 1)
			ssa->count += rra(ssa, a);
*/