/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cocktail.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <tbelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 14:46:28 by tbelard           #+#    #+#             */
/*   Updated: 2025/12/28 17:07:29 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static size_t	ft_cut_in2(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	int	i;
	int count;

	count  = 0;
	i = ssa->size;
	while (ssa->size > ((i / 2) + ssa->odd))
	{
		if (a[ssa->head].val < (i / 2))
			count += pb(ssa, ssb, a, b); 
		else
			count += ra(ssa, a);
	}
	if (ssa->odd)
		count += ra(ssa, a);
	ssa->end_l = a[ssa->head].prev;//init des bornes
	ssb->end_l = b[ssb->head].prev;
	ssa->start_l = ssa->head;
	ssb->start_l = ssb->head;
	ssa->top_phys = ssa->head;
	ssb->top_phys = ssb->head;
	return (count);
}

int	check_the_cocktail(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	if (ssa->odd)
	{
		if (ssa->flag)
			ssa->count += ra(ssa, a);
		else
			ssa->count += rra(ssa, a);
		if (a[ssa->head].val > a[a[ssa->head].next].val)
			ssa->count += sa(ssa, a);
	}
	if (ssa->flag)
	{
		ssa->end_l = ssa->head;
		ssb->end_l = ssb->head;
	}
	else
	{
		ssa->count += rr(ssa, ssb, a, b);
		ssa->start_l = ssa->head;
		ssb->start_l = ssb->head;
	}
	if (ssa->end_l == ssa->start_l || ssb->end_l == ssb->start_l)
		return (1);
	return (0);
}
void	petite_ombrelle(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	while (b[ssb->head].val != ssb->size - 1
		|| a[ssa->head].val != ssa->size)
	{
		if (b[ssb->head].val != ssb->size - 1
		&& a[ssa->head].val != ssa->size - ssa->odd)
			ssa->count += rr(ssa, ssb, a, b);
		else
			ssa->count += ra(ssa, a);
	}
	if (ssa->odd)
		ssa->count += rra(ssa, a);
	while (ssb->size)
		ssa->count += pa(ssa, ssb, a, b);
	ssa->start_l = ssa->head;
}

void	aller_retour(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	while (1)
	{
		if (a[ssa->head].val > a[a[ssa->head].next].val
		&& (b[ssb->head].val < b[b[ssb->head].next].val))
			ssa->count += ss(ssa, ssb, a ,b);
		else if (a[ssa->head].val > a[a[ssa->head].next].val)
			ssa->count += sa(ssa, a);
		else if (b[ssb->head].val < b[b[ssb->head].next].val)
			ssa->count += sb(ssb, b);
		if (ssa->flag)
		{
			if (a[ssa->head].next == ssa->end_l
			|| b[ssb->head].next == ssb->end_l)
				break ;
			ssa->count += rr(ssa, ssb, a, b);
		}
		else
		{
			if (a[ssa->head].prev == a[ssa->start_l].prev
			 || b[ssb->head].prev == b[ssb->start_l].prev)
				break ;
			ssa->count += rrr(ssa, ssb, a, b);
		}
	}	
}

void	cocktail(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	ssa->top_phys = ssa->head;
	ssb->top_phys = ssb->head;
	ssa->start_l = ssa->head;
	if (!(isNot_sorted(*ssa, *ssb, a, b)))
		return ;
	ssa->odd = (ssa->size % 2 == 1);
	ssa->count = ft_cut_in2(ssa, ssb, a, b);
	while (isNot_sorted(*ssa, *ssb, a, b))
	{
		ssa->flag = 1;
		aller_retour(ssa, ssb, a, b);
		if (check_the_cocktail(ssa, ssb, a, b))
			break ;
		ssa->flag = 0;
		aller_retour(ssa, ssb, a, b);
		if (check_the_cocktail(ssa, ssb, a, b))
			break ;
	}
	petite_ombrelle(ssa, ssb, a, b);
}