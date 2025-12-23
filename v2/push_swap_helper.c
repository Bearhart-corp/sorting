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

void	algo_3move(t_meta *ssa, t_stack *a)//MARCHE QUE SI NORMALISE et size = 3
{
	int	i;

	i = ssa->head;			//tete doit etre sur le top
	if (a[ssa->head].val > a[a[ssa->head].next].val
		&& a[ssa->head].val > a[a[a[ssa->head].next].next].val)
		ra(ssa, a);
	else if (a[a[ssa->head].next].val >
		a[a[a[ssa->head].next].next].val)
		rra(ssa, a);
	if (a[ssa->head].val > a[a[ssa->head].next].val)
		sa(ssa, a);
	//possibilites

	//012	->				top = gauche | deja triee
	//021	->	rra + sa

	//210	->	sa + rra			
	//201	->	ra

	//120	->	rra
	//102	->	sa
	
}

void	ft_print_stack(t_meta ssa, t_meta ssb, t_stack *a, t_stack *b)
{
	printf("\n\tETAT STACK A\n\n");
	ssa.head = ssa.start;
	ssb.head = ssb.start;
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

size_t	find_end(size_t size, size_t head, t_stack *a)
{
	while (--size)
		head = a[head].next;
	return (head);
}

int	find_start(size_t size, int head, t_stack *a)
{
	while (--size)
		head = a[head].prev;
	return (head);
}

void	ft_push_swap(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	/*
	>alors il faut borner pour ne pas melanger les ra qui avancent
	et les ra qui trient
	> il faut avec 2 bornes start et end
	> le pong reduit le nombres de coup considerablement
	> il faut bien gerer le cas des impairs qui provequent une assymetrie
	> Bon courage a nous !

	*/
	int		i;
	int		j;
	char	even;
	int 	count;

	count = 0;
	i = ssa->size;
	ssa->start = ssa->head;
	ssb->start = ssb->head;
	even = (i % 2 == 0); //i aka n_elem is odd ?
	if (!(isNot_sorted(*ssa, *ssb, a, b)))
		return (ft_print_stack(*ssa, *ssb, a, b));
	if (i < 4)
		return (algo_3move(ssa, a));
	while (ssa->size > (i / 2) + !even) //la size est VARIABLE, modifie par pb et pa !
	{
		if (a[ssa->head].val < (i / 2))
		{
			pb(ssa, ssb, a, b); 
			count++;
		}
		else
		{
			ra(ssa, a);
			count++;
		}
	}
	if (!even)
		ra(ssa, a); count++;
	ssa->start = ssa->head;
	ssb->start = ssb->head;
	i = 0;
	//printf("|%d| 1 = not sorted et 0 = sorted", isNot_sorted(*ssa, *ssb, a, b));
	while (isNot_sorted(*ssa, *ssb, a, b))//tant que pas trier
	{
		ssa->end_l = find_end(ssa->size - i, ssa->start, a);
		ssa->start_l = find_start(ssa->size - i, a[ssa->start].prev, a);
		ssa->head = ssa->start_l;
		printf("head%zu\n", ssa->head );
		while (ssa->head != ssa->end_l)
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
		
		rrr(ssa, ssb,a ,b);
		
		
		while (ssa->head != a[ssa->start_l].prev)
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
			rrr(ssa, ssb, a, b);
		}
		i++;
		count++;
		rr(ssa, ssb, a, b);
	}
	ft_print_stack(*ssa, *ssb, a, b);
	while (b[ssb->head].val != ssb->size - 1)
	{
		count++;
		rb(ssb, b);
	}
	while (a[ssa->head].val != ssa->size)
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
	printf("count :%d\n",count);
	/*
	commence par implementer bubble sort avec tech:
		push b tous les legers
		fais ton ping pong sur les 2 stacks a la fois pour rr
		B doit etre a l'envers !
		rotate n / 2 les 2 stacks
		push b (tout) sur a puis return;*/
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