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

void	algo_3move(t_meta ssa, int *a)//MARCHE QUE SI NORMALISE
{
	int	i;

	i = ssa.head;					//tete doit etre sur le top
	if (a[i] >> VALUE & MASK == 0)
	{
		if ((a[i & MASK] >> VALUE & MASK) == 1) //si next = 1 
			return ;				//deja triee
		rra(ssa, a);
		return (sa(ssa, sa));
	}								//bottom = a droite !
	if (a[i] >> VALUE & MASK == 2)
	{
		if ((a[i & MASK] >> VALUE & MASK) == 0)
			return (ra(ssa, sa));
		sa(ssa, sa);
		return (rra(ssa, a));
	}
	if ((a[i & MASK] >> VALUE & MASK) == 0)
		return (sa(ssa, sa));
	return (rra(ssa, sa));

	//possibilites

	//012	->				top = gauche | deja triee
	//021	->	rra + sa

	//210	->	sa + rra			
	//201	->	ra

	//120	->	rra
	//102	->	sa
}

void	ft_push_swap(t_meta ssa, t_meta ssb, int *a, int *b)
{
	int		i;
	int		j;
	char	even;

	i = ssa.size;
	while (i--)
	{
		if (a[ssa.head] < ssa.size / 2)
			pb(ssa, ssb, a, b);
		ra(ssa, a);
	}
	noteven = ssa.size & 1; //size aka n_elem is pair ?
	i = ssa.size / 2;
	if (i < 4)
		return (algo_3move(ssa, a), ); //ne rentre jamais si i = 1
	while (i > 1)
	{
		j = --i; //pour i = 4 depart i:3 et j:3 then i:2 et j:2
		while (i--)
		{
			if (a[ssa.head] > a[a[ssa.head & MASK]])//next
			{
				if (b[ssb.head] < b[b[ssb.head & MASK]]) //reverse !!
					ss(ssa, ssb, a, b);
				else
					sa(ssa, a);
			}
			else if (b[ssb.head] < b[b[ssb.head & MASK]])
				sb(ssb, b);
			rr(ssa, ssb, a, b);
		}
		i = j;
		while ((i-- - noteven) > 0)//pong, on part dans l'autre sens
		{ //si pair
			if (a[ssa.head] < a[a[ssa.head & (MASK << 10)]])//prev
			{
				if (b[ssb.head] > b[b[ssb.head & (MASK << 10)]]) //reverse !!
					ss(ssa, ssb, a, b);
				else
					sa(ssa, a);
			}
			else if (b[ssb.head] > b[b[ssb.head & (MASK << 10)]])
				sb(ssb, b);
			rrr(ssa, ssb, a, b);
		}
	}
	while ((ssa.size-- - noteven) > 0)
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

void	*ft_memcpy(void *dest, const void *src, size_t n_byte)
{
    unsigned char 			*d;
    const unsigned char 	*s;

    if (n_byte == 0)
    	return (dest);
    if (!dest || !src)
        return NULL;
    d = (unsigned char *)dest;
    s = (const unsigned char *)src;

    if ((((uintptr_t)d ^ (uintptr_t)s) & (sizeof(size_t) - 1)) == 0)
    {
        while (((uintptr_t)d & (sizeof(size_t) - 1)) && n_byte--)
            *d++ = *s++;
        while (n_byte >= sizeof(size_t))
        {
            *(size_t *)d = *(const size_t *)s;
            d += sizeof(size_t);
            s += sizeof(size_t);
            n_byte -= sizeof(size_t);
        }
    }
    while (n_byte--)
		*d++ = *s++;
    return (dest);
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
	a[i] |= (MAX_NBR - 1) << INDEX_PREV;
}
/*498 <- 499 next-> 500 - n_elem
*/

0101
0000