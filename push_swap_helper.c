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

void	*ft_memcpy(void *dest, const void *src, size_t n_byte)
{
    unsigned char 	*d;
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

void	ra(t_ring *r)//le premier devient le dernier, move vers le haut
{
	if (r->size >= 2)
		r->top_logik++;
}

void	rra(t_ring *r)//le dernier devient le premier, move vers le bas
{
	if (r->size >= 2)
		r->top_logik--;
}

int	pop(t_ring *r)
{
	int	out;

	if (r->size > 0)
	{
		out = r->top_phys;
		r->top_phys = (r->top_phys + 1) % r->n;
		return (r->size--, out);
	}
	return (0);//id (r.size == 0) return //si rien a pop cote appelant ret
}

int	push(t_ring *r)
{
	if (r->size < r->n)
	{
		r->top_phys = (r->top_phys - 1) % r->n;
		r->size++;
		return (1);
	}
	return (0);//ERROR
}

void	init(t_ring *stk, int n_elem, int *tab)
{
	if (n_elem == 0 || !stk)
		return ;
	stk->ring = malloc(n_elem * sizeof(int));
	stk->size = n_elem;
	stk->n = n_elem;
	stk->top_phys = 0;
	stk->top_logik = 0;
	if (tab)
		stk->ring = ft_memcpy(stk->ring, tab, n_elem * sizeof(int));
}
/*
	int	*ring;
	int	top_phys;
	int	n;
	int	size;
	int	top_logik;
*/

/*
donc pour rendre possibile le circulaire avec le fameux cas du push
avec une head au milieu la formule est = (index_head + (i % size) % n)
ex: stack n = 7; size = 7

0	i = 3
1	i = 4
2	i = 5
3	//start middle ! head et on pop -> size = 6 
//////// i = 6 et donc (4 + (6 % 6)) % 7 = 4 (on passe donc de 2 a 4 directement)
4	nouvelle head ; i = 0
5	curseur = (index_head + (i % size) % n)
6	donc (4 + (2 % 6)) % 7