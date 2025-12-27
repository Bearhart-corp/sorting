/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 13:09:37 by tbelard           #+#    #+#             */
/*   Updated: 2025/12/14 13:09:41 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
		size;	//n_elem
		head;	//pointe de lecture
		cap;	//MAX_NBR
		free	//stack free
		ifree	//spx free
*/

size_t	algo_3move(t_meta *ssa, t_stack *a)
{
	size_t	count;

	count = 0;
	if (a[ssa->head].val > a[a[ssa->head].next].val
		&& a[ssa->head].val > a[a[a[ssa->head].next].next].val)
	{
		ra(ssa, a);
		count++;
	}
	else if (a[a[ssa->head].next].val >
		a[a[a[ssa->head].next].next].val)
	{
		rra(ssa, a);
		count++;
	}
	if (a[ssa->head].val > a[a[ssa->head].next].val)
	{
		sa(ssa, a);	
		count++;
	}
	return (count);
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

int	isNot_sorted(t_meta ssa, t_meta ssb, t_stack *a, t_stack *b)
{
	while (ssa.size-- > 1)
	{
		if (a[ssa.start].val > a[a[ssa.start].next].val)
			return (1);
		ssa.start = a[ssa.start].next;
	}
	while (ssb.size-- > 1)
	{
		if (b[ssb.start].val < b[b[ssb.start].next].val)
			return (1);
		ssb.start = b[ssb.start].next;
	}
	return (0); //is sorted
}

size_t	ft_cut_in2(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	int	odd;
	int	i;

	i = ssa->size;
	odd = (i % 2 == 1);
	if (i < 4)
		return (algo_3move(ssa, a));
	while (ssa->size > (i / 2) + odd)
	{
		if (a[ssa->head].val < (i / 2))
			pb(ssa, ssb, a, b); 
		else
			ra(ssa, a);
	}
	if (!odd)
		ra(ssa, a);
	ssa->end_l = a[ssa->head].prev;//init des bornes
	ssb->end_l = b[ssb->head].prev;
	ssa->start_l = ssa->head;
	ssb->start_l = ssb->head;
	return (i);
}

void	ft_push_swap(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	int	count;
	int	odd;

	odd = (ssa->size % 2 == 1); //doublon de code !!!
	count = ft_cut_in2(ssa, ssb, a, b);
	
	while (isNot_sorted(*ssa, *ssb, a, b))
	{
		while (1)
		{
			if (a[ssa->head].val > a[a[ssa->head].next].val
			&& (b[ssb->head].val < b[b[ssb->head].next].val))
				count += ss(ssa, ssb, a ,b);
			else if (a[ssa->head].val > a[a[ssa->head].next].val)
				count += sa(ssa, a);
			else if (b[ssb->head].val < b[b[ssb->head].next].val)
				count += sb(ssb, b);
			if (a[ssa->head].next == ssa->end_l
				|| b[ssb->head].next == ssb->end_l)
				break ;
			count += rr(ssa, ssb, a, b);
		}
		if (odd)
		{
			count += ra(ssa, a);
			if (a[ssa->head].val > a[a[ssa->head].next].val)
				count += sa(ssa, a);
		}
		ssa->end_l = ssa->head;
		ssb->end_l = ssb->head;
		if (ssa->end_l == ssa->start_l
			|| ssb->end_l == ssb->start_l)
			break ;
		while (1)
		{
			if (a[ssa->head].val > a[a[ssa->head].next].val
				&& (b[ssb->head].val < b[b[ssb->head].next].val))
				count += ss(ssa, ssb, a ,b);
			else if (a[ssa->head].val > a[a[ssa->head].next].val)
				count += sa(ssa, a);
			else if (b[ssb->head].val < b[b[ssb->head].next].val)
				count += sb(ssb, b);
			if (a[ssa->head].prev == a[ssa->start_l].prev
			 || b[ssb->head].prev == b[ssb->start_l].prev)
				break ;
			count += rrr(ssa, ssb, a, b);
		}
		if (odd)
		{
			count += rra(ssa, a);
			if (a[ssa->head].val > a[a[ssa->head].next].val)
				count += sa(ssa, a);
		}
		count += rr(ssa, ssb, a, b); // vas sur le + 1;
		ssa->start_l = ssa->head;
		ssb->start_l = ssb->head;
		if (ssa->end_l == ssa->start_l
			|| ssb->end_l == ssb->start_l)
			break ;
	}

	while (b[ssb->head].val != ssb->size - 1
		|| a[ssa->head].val != ssa->size)
	{
		if (b[ssb->head].val != ssb->size - 1
		&& a[ssa->head].val != ssa->size - odd)
			count += rr(ssa, ssb, a, b);
		else
			count += ra(ssa, a);
	}
	if (odd)
		count += rra(ssa, a);
	while (ssb->size)
		count += pa(ssa, ssb, a, b);
	ssa->start_l = ssa->head;
	ft_print_stack(*ssa, *ssb, a, b);
	printf("count :%d\n",count);
}

void	init(int n_elem, t_stack *a, t_stack *b)
{
	int i;
	int	j;

	i = MAX_NBR - 1;
	j = 0;
	a[i].next = MAX_NBR - n_elem;
	while (--n_elem)
	{
		a[i--].prev = (MAX_NBR - 2 - j);
		a[i].next = ((MAX_NBR - 1 - j) % MAX_NBR);
		j++;
	}
	a[i].next = MAX_NBR - j;
	a[i].prev = MAX_NBR - 1; //on le fait pointer vers le dernier
	i = 0;
	while (i < n_elem)
		b[i++].val = 0;
}

void	init_meta_data(t_meta *ssa, t_meta *ssb, int n_elem)
{
	ssa->size = (size_t)n_elem; 				//full
	ssb->size = 0; 								//vide
	ssa->head = (size_t)(MAX_NBR - n_elem);		//TOP STACK verif que c 504
	ssb->head = (size_t)MAX_NBR - 1;				//tout en bas
	ssa->ifree = MAX_NBR;	// a verifier depassement
	ssb->ifree = 0;				//FULL et commence a 511
	while (ssb->ifree < MAX_NBR)
	{
		ssb->free[ssb->ifree] = ssb->ifree;
		ssb->ifree++;
	}
	ssb->ifree = 0; //full donc index sur le top de la stack
}

/*

BUBBLE SIMPLE

int		i;
	int		j;
	char	noteven;
	int 	count;

	count = 0;
	i = ssa->size;
	noteven = i & 1; //i aka n_elem is odd ?
	if (i < 4)
		return (algo_3move(ssa, a));
	while (ssa->size > (i / 2) + noteven) //la size est VARIABLE, modifie par pb et pa !
	{
		if (a[ssa->head].val < (i / 2))
			pb(ssa, ssb, a, b);
		else
			ra(ssa, a);
	}
	i = 0;
	j = 0;
	while (j < (ssa->size) + noteven)
	{
		i = 0;
		while (++i < (ssa->size))
		{
			if (a[ssa->head].val > a[a[ssa->head].next].val
				&& (b[ssb->head].val < b[b[ssb->head].next].val))
			{
				ss(ssa, ssb, a ,b);
				count++;
			}
			else if (a[ssa->head].val > a[a[ssa->head].next].val)
			{
				count++;
				sa(ssa, a);
			}
			else if (b[ssb->head].val < b[b[ssb->head].next].val)
			{
				count++;
				sb(ssb, b);
			}
			count++;
			rr(ssa, ssb, a, b);
		}
		count++;
		rr(ssa, ssb, a, b);
		j++;
	}

	while (b[ssb->head].val != ssb->size - 1)
	{
		count++;
		rb(ssb, b);
	}
	i = 0;
	while (i++ < ssa->size)
	{
		count++;
		ra(ssa, a); //car lelem le+ petit est forcement size or size - 1
	}
	
	while (ssb->size)
	{
		count++;
		pa(ssa, ssb, a, b);
	}
	ssa->start = ssa->head;
	ft_print_stack(*ssa, *ssb, a, b);
	printf("count = %d\n", count);
		
*/