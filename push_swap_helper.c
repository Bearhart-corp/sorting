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

void	algo_3move(t_meta *ssa, int *a)//MARCHE QUE SI NORMALISE et size = 3
{
	int	i;

	i = ssa->head;			//tete doit etre sur le top
	if ((a[i] >> VALUE & MASK) == 0)
	{	
		if ((a[a[i] & MASK] >> VALUE & MASK) == 1) //si next = 1 
			return ;				//deja triee
		rra(ssa, a);
		return (sa(ssa, a));
	}								//bottom = a droite !
	if ((a[i] >> VALUE & MASK) == 2)
	{
		if ((a[a[i] & MASK] >> VALUE & MASK) == 0)
			return (ra(ssa, a));
		sa(ssa, a);
		return (rra(ssa, a));
	}
	if ((a[a[i] & MASK] >> VALUE & MASK) == 0)
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

void	ft_push_swap(t_meta *ssa, t_meta *ssb, int *a, int *b)
{
	int		i;
	int		j;
	char	noteven;

	i = ssa->size;
	if (i < 4)
		return (algo_3move(ssa, a));
	while (ssa->size > (i / 2)) //la size est VARIABLE, modifie par pb et pa !
	{
		if ((a[ssa->head] >> VALUE & MASK) < (i / 2))
			pb(ssa, ssb, a, b);
		else
			ra(ssa, a);
	}
	noteven = i & 1; //i aka n_elem is odd ?
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
				{
					
					sa(ssa, a);
				}
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
		printf("stack A\n");
		for(int p = 0; p < 2; p++)
		{
			printf("%d:%d\n",p , (a[ssa->head] >> VALUE ) & MASK);
			ssa->head = a[ssa->head] & MASK;
		}
		printf("stack B\n");
		for(int p = 0; p < 2; p++)
		{
			printf("%d:%d\n",p , (b[ssb->head] >> VALUE ) & MASK);
			ssb->head = b[ssb->head] & MASK;
		}
		exit(1);
	}

	while (ssb->size > 0)
		pa(ssa, ssb, a, b);
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

void	init(int n_elem, int *a)
{
	int i;
	int	j;

	i = MAX_NBR - 1;
	
	a[i] = a[i] << VALUE; // on lui attribut sa valeur
	a[i] |= (MAX_NBR - n_elem);//le dern dela stat-> le premier(next)
	a[i] |= (IN_A << CTRL);
	a[i--] |= ((MAX_NBR - 2) << INDEX_PREV);//prev
	j = 1;
	while (--n_elem)
	{
		a[i] = a[i] << VALUE;
		a[i] |= (IN_A << CTRL); // set up la bit de controle a IN_A
		a[i] |= ((MAX_NBR - 2 - j) << INDEX_PREV); // il pointe le noeud derrier
		a[i] |= (MAX_NBR - j);//next
		j++;
		i--;
	}
	i++;
	a[i] &= 0xfff003ff;
	a[i] |= (MAX_NBR - 1) << INDEX_PREV; //on le fait pointer vers le dernier
}

void	init_meta_data(t_meta *ssa, t_meta *ssb, int n_elem)
{
	int	i;

	i = -1;
	ssa->size = (size_t)n_elem; 				//full
	ssb->size = 0; 								//vide
	ssa->head = (size_t)(MAX_NBR - n_elem);		//TOP STACK verif que c 504
	ssb->head = (size_t)MAX_NBR; 				//tout en bas
	ssa->cap = MAX_NBR;
	ssb->cap = MAX_NBR;
	ssa->ifree = 0;				//vide et commence a 0
	ssb->ifree = MAX_NBR - 1;	//pleine et commence a max - 1 
	ssa->free[0] = 0;
	while (++i < MAX_NBR)
		ssb->free[i] = i;
}


/*498 <- 499 next-> 500 - n_elem
*/

