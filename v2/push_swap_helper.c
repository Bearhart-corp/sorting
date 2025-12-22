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
	if (a[i].val == 0)
	{	
		if (a[a[i].next].val == 1) //si next = 1 
			return ;				//deja triee
		rra(ssa, a);
		return (sa(ssa, a));
	}								//bottom = a droite !
	if (a[a[i].next].val == 2)
	{
		if (a[a[i].next].val == 0)
			return (ra(ssa, a));
		sa(ssa, a);
		return (rra(ssa, a));
	}
	if (a[a[i].next].val == 0)
		return (sa(ssa, a));
	return (rra(ssa, a));

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

void	ft_push_swap(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	int		i;
	int		j;
	char	noteven;

	i = ssa->size;
	if (i < 4)
		return (algo_3move(ssa, a));
	while (ssa->size > (i / 2)) //la size est VARIABLE, modifie par pb et pa !
	{
		if (a[ssa->head].val < (i / 2))
			pb(ssa, ssb, a, b);
		else
			ra(ssa, a);
	}
	noteven = i & 1; //i aka n_elem is odd ?
	i = 0;
	j = 0;
	while (j < (ssa->size) + noteven)
	{
		i = 0;
		while (++i < (ssa->size))
		{
			if (a[ssa->head].val > a[a[ssa->head].next].val)
			{
				sa(ssa, a);
			}
			if (b[ssb->head].val < b[b[ssb->head].next].val)
			{
				sb(ssb, b);
			}
			rr(ssa, ssb, a, b);
		}
		rr(ssa, ssb, a, b);
		
		j++;
	}

	while (b[ssb->head].val != 0)
		rb(ssb, b);
	i = 0;
	while (i++ < ssa->size)
		ra(ssa, a); //car lelem le+ petit est forcement size or size - 1
	while (ssb->size)
		pa(ssa, ssb, a, b);
ft_print_stack(*ssa, *ssb, a, b);
	
	
	/*
	commence par implementer bubble sort avec tech:
		push b tous les legers
		fais ton ping pong sur les 2 stacks a la fois pour rr
		B doit etre a l'envers !
		rotate n / 2 les 2 stacks
		push b (tout) sur a return;

	implementation de radix binaire (tente en 4 coins si possible)
	implementation du turk algo
	testing and improvement if its working
	*/
}

void	init(int n_elem, t_stack *a)
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
}

void	init_meta_data(t_meta *ssa, t_meta *ssb, int n_elem)
{
	ssa->size = (size_t)n_elem; 				//full
	ssb->size = 0; 								//vide
	ssa->head = (size_t)(MAX_NBR - n_elem);		//TOP STACK verif que c 504
	ssb->head = (size_t)MAX_NBR - 1;				//tout en bas
	ssa->cap = MAX_NBR;
	ssb->cap = MAX_NBR;
	ssa->ifree = MAX_NBR;	//vide et commence a 511
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

	noteven = i & 1; //i aka n_elem is odd ?
	i = 0;
	j = 0;
	while (j < (ssa->size / 2) + noteven)
	{
		while (++i < ssa->size - j)
		{
			if (a[ssa->head].val > a[a[ssa->head].next].val)
				sa(ssa, a);
			ra(ssa, a);
		}
		while (--i > 0 + j)
		{
			if (a[ssa->head].val > a[a[ssa->head].next].val)
				sa(ssa, a);
			rra(ssa, a);
		}
		j++;
	}
	while (a[ssa->head].val != 0)
		ra(ssa, a); //infinite avec le nouvel algo car aucun 0 dans A! ^^

		//////////BUBBLE AMELIORER

			i = ssa->size; // si size de 4 maintenant elle vaut 2 !
	while (i > 1)
	{
		j = --i; //pour i = 4 depart i:3 et j:3 then i:2 et j:2
		while (i-- > 0)
		{
			if ((a[ssa->head] >> VALUE & MASK) > (a[a[ssa->head] & MASK]
						>> VALUE & MASK))//next
			{
				if ((b[ssb->head] >> VALUE & MASK) < (b[b[ssb->head] & MASK]
								>> VALUE & MASK)) //reverse !!
					ss(ssa, ssb, a, b);
				else
					sa(ssa, a);
			}
			else if ((b[ssb->head] >> VALUE & MASK) < (b[b[ssb->head] & MASK]
							>> VALUE & MASK))
				sb(ssb, b);
			rr(ssa, ssb, a, b);
		}
		i = j;
		while ((i-- - noteven) > 0)//pong, on part dans l'autre sens
		{ //si pair
			if ((a[ssa->head] >> VALUE & MASK) < (a[a[ssa->head] & MASK]
						>> VALUE & MASK))//prev
			{
				if ((b[ssb->head] >> VALUE & MASK) > (b[b[ssb->head] & MASK]
								>> VALUE & MASK)) //reverse !!
					ss(ssa, ssb, a, b);
				else
					sa(ssa, a);
			}
			else if ((b[ssb->head] >> VALUE & MASK) > (b[b[ssb->head] & MASK]
							>> VALUE & MASK))
				sb(ssb, b);
			rrr(ssa, ssb, a, b);
		}
	}
	while (ssb->size > 0)
		pa(ssa, ssb, a, b);
*/

