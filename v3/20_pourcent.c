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
		return (count >= (ssa.size / 2));
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

char	find_smallest_bigger_inA(t_meta ssa, t_meta ssb, t_stack *a, t_stack *b)
{
	short 	count;
	ssize_t	lenght;

	count = 0;
	lenght = ssa.size;
	if (ssa.size == 0)
		return (0);
	while (lenght-- > 0)
	{
		if (a[ssa.head].val < ssb.target && 
				ssb.target < a[a[ssa.head].next].val)
				break ;
		ssa.head = a[ssa.head].next;
		count++;
	}
	return (count >= ssa.size / 2);
}

static void	insert(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	char	bol;
	ssize_t	lenght;

	lenght = ssa->size;
	while (ssb->size)
	{
		ssb->target = b[ssb->head].val; //on veut trouver ou inserer target
		bol = find_smallest_bigger_inA(*ssa, *ssb, a, b);
		while (lenght-- > 0)
		{
			//ft_print_stack(*ssa, *ssb, a, b);
			if (a[ssa->head].val < ssb->target && 
				ssb->target < a[a[ssa->head].next].val)
				break ;
			if (bol)
				ssa->count += rra(ssa, a);
			else
				ssa->count += ra(ssa, a);
		}
		ssa->count += ra(ssa, a);
		ssa->count += pa(ssa, ssb, a ,b);
	}
}

void	vingt_pour_100(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	char	bol;

	ssa->count = 0;
	ssa->start_l = ssa->head;
	ssa->end_l = a[ssa->head].prev;
	while (ssa->head != ssa->end_l && desorder(*ssa, *ssb, a, b) != 0 )
	{
		if (a[ssa->head].val > a[a[ssa->head].next].val)
		{
			if (a[a[ssa->head].prev].val > a[ssa->head].val)
				ssa->count += pb(ssa, ssb, a, b);
			ssa->count += ra(ssa, a);
		}
		else if (a[a[ssa->head].prev].val > a[ssa->head].val)
			ssa->count += pb(ssa, ssb, a, b);
		else
			ssa->count += ra(ssa, a);
	}
	ssa->count += ra(ssa, a);
	ft_print_stack(*ssa, *ssb, a, b);
	insert(ssa, ssb, a, b);
	ssb->target = 0;
	bol = find_smallest_bigger_inA(*ssa, *ssb, a, b);
	while (a[ssa->head].val != 0)
	{
		if (bol)
			ssa->count += rra(ssa, a);
		else
			ssa->count += ra(ssa, a);
	}
}
