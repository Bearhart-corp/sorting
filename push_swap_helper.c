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

void	init(int n_elem, int *a)
{
	//convention = bit:31-30 = ctrl 
	//(possible state: 00:free, 01:In_A, 10:In_B, 11:Undefined
	//bit:29-20 = valeur (0 to 2047 ce qui suffit pour push_swap)
	//bit:19-10 = Index_prev (pointe vers l'index du noeud suivant)
	//bit:9-0	= Index_next
	int i;

	i = 0;
	while (i < n_elem)
	{
		a[i] |= (IN_A << CTRL); // set up la bit de controle a IN_A
		a[i] |= ((i + n_elem - 1) << INDEX_PREV); // il pointe le noeud derriere
		a[i] |= (i + 1) % n_elem; //le noeud devant
		i++;
	}
}