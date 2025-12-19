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

void	ft_push_swap(t_meta ssa, t_meta ssb, int *a, int *b)
{
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