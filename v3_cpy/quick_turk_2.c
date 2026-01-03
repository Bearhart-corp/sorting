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
	int i;

	while (ssa->size > 3)
		quick_2(ssa, ssb, a, b);
	algo_2move(ssa, a);
	i = 0;
	while (ssb->size)
	{
		
		while (b[ssb->head].val < b[b[ssb->head].prev].val
		&& b[ssb->head].val > b[b[ssb->head].next].val)
			ssa->count += rrb(ssb, b);
		while (b[ssb->head].val < b[b[ssb->head].next].val)
			ssa->count += sb(ssb, b);
		if (b[ssb->head].val < a[ssa->head].val)
		{
			if (a[a[ssa->head].prev].val > b[ssb->head].val && i > 0)
			{
				ssa->count += rra(ssa, a);
				i--;
			}
			else
				ssa->count += pa(ssa, ssb, a, b);
		}	
		else if (b[ssb->head].val > a[ssa->head].val)
		{
			ssa->count += ra(ssa, a);
			i++;
		}
	}
	//if (ssb->size == 250)
}
/*
pseudo code =

0/ i représente le nombre de valeurs en attente dans le bottom de A

1/ choix entre top B, next B, et prev B. //avec les 2 while

2/si top B < top A ET top B > bottom A ET que bottom exist
     2.1/si il y a un bottom A (valeurs en attente) si bottom A > top B alors on ramène bottom A au top (i--)
     sinon
     pa

3/Si ya pas plus grand sur top B que le plus grand dans bottom A on rotate tout.
*/
