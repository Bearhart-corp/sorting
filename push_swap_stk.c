/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_stk.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:25:17 by tbelard           #+#    #+#             */
/*   Updated: 2025/12/18 12:25:19 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//convention :			bit:31-30 = ctrl 

	//(possible state: 	00:free, 01:In_A, 10:In_B, 11:Undefined
	//bit:29-20 = 		valeur (0 to 2047 ce qui suffit pour push_swap)
	//bit:19-10 = 		Index_prev (pointe vers l'index du noeud suivant)
	//bit:9-0	= 		Index_next

//Valeurs partager:

	//struct : size			:	nb_element actuel
	//struct : head			:	index du top de la stack
	//struct : cap			:	taille du buffer
	//struct : *free_lst	:	list free
	//struct : ifree		:	index en cours de free pour acces O/1

//	define:

	//	INDEX_PREV 	0xa
	//	MASK 		0x3ff
	//	VALUE 		0x14
	//	CTRL 		0x1e
	//	IN_A 		1
	//	IN_B 		2
	//	FREE 		0

void	ra(t_meta ssa, int *a)//le premier devient le dernier, move vers le haut
{
	ssa.head = a[ssa.head & MASK];//index du top = top->next
}

void	rra(t_meta ssa, int *a)//le dernier devient le premier, move vers le bas
{
	ssa.head = a[(ssa.head >> INDEX_PREV)& MASK];//index du top = top->prev
}

void	rb(t_meta ssb, int *b)
{
	ssb.head = b[ssb.head & MASK];
}

void	rrb(t_meta ssb, int *b)
{
	ssb.head = b[(ssb.head >> INDEX_PREV)& MASK];
}

void	rrr(t_meta ssa, t_meta ssb, int *a, int *b)
{
	rra(ssa, a);
	rrb(ssb, b);
}

void	rr(t_meta ssa, t_meta ssb, int *a, int *b)
{
	ra(ssa, a);
	rb(ssb, b);
}

void	sa(t_meta ssa, int *a)
{
	short	next;
	int		tmp;

	if (ssa.size < 2)
		return ;
	next = a[ssa.head & MASK]; //next = head.next
	if (a[ssa.head] == a[next])
		return ;
	tmp = a[ssa.head] & 0x3ff00000; // recup de .value a son index 
	a[ssa.head] = (a[ssa.head] & 0xc00fffff) | (next & 0x3ff00000);
	//head.value = next.value
	a[next] = (a[next] & 0xc00fffff) | tmp;// next.value = .value
}

void	sb(t_meta ssb, int *b)
{
	short	next;
	int		tmp;

	if (ssb.size < 2)
		return ;
	next = b[ssb.head & MASK];
	if (b[ssb.head] == b[next])
		return ;
	tmp = b[ssb.head] & 0x3ff00000; 
	b[ssb.head] = (b[ssb.head] & 0xc00fffff) | (next & 0x3ff00000);
	b[next] = (b[next] & 0xc00fffff) | tmp;
}

void	ss(t_meta ssa, t_meta ssb, int *b, int *a)
{
	sa(ssa, a);
	sb(ssb, b);
}

void	pa(t_meta *ssa, t_meta *ssb, int *a, int *b)
{
	short	value;
	short	index_node;

	value = (b[ssb->head] & 0x3ff00000);
	//pop b push sur a
	b[ssb->head] &= 0x3fffffff; // n'est plus utilise dans A ou B (donc free)
	ssb->free[ssb->ifree++] = ssb->head; //on le push dans la liste free

	b[b[ssb->head] & MASK] &= 0xfff003ff; // next->prev = 0
	b[b[ssb->head] & MASK] |= ((b[ssb->head] >> INDEX_PREV) & MASK);
	//next->prev = prev;
	b[(b[ssb->head] >> INDEX_PREV) & MASK] &= 0xfffffc00; //prev->next = 0;
	b[(b[ssb->head] >> INDEX_PREV) & MASK] |= b[b[ssb->head] & MASK];
	 //prev->next = next;
	//////////////PUSH
	//on se met sur le top de la stack free
	if (ssa->ifree > 0)
	{
		ssa->ifree -= 1;
		index_node = ssa->free[ssa->ifree];
	}
	a[index_node] |= 0x40000000; //in_a
	a[index_node] &= 0xfff003ff; //node.prev = 0 then head.prev
	a[index_node] |= (a[ssa->head] >> INDEX_PREV) & MASK;
	a[ssa->head] &= 0xfff003ff; // head.prev = 0
	a[ssa->head] |= index_node;
	a[index_node] &= 0xfffffc00; // node.next = 0;
	a[index_node] |= ssa->head; // node.next = 0;
	a[index_node] &= 0xc00fffff; //value = 0;
	a[index_node] |= value;
}

void	pb(t_meta *ssa, t_meta *ssb, int *a, int *b)
{
	short	value;
	short	index_node;

	value = (b[ssb->head] & 0x3ff00000);
	//pop b push sur a
	a[ssa->head] &= 0x3fffffff; // n'est plus utilise dans A ou B (donc free)
	ssa->free[ssa->ifree++] = ssa->head; //on le push dans la liste free
	//celui avant doit pointer vers celui apres et celui apres avant

	a[a[ssa->head] & MASK] &= 0xfff003ff; // next->prev = 0
	a[a[ssa->head] & MASK] |= ((a[ssa->head] >> INDEX_PREV) & MASK);
	//next->prev = prev;
	a[((a[ssa->head] >> INDEX_PREV) & MASK)] &= 0xfffffc00; //prev->next = 0;
	a[((a[ssb->head] >> INDEX_PREV) & MASK)] |= a[a[ssa->head] & MASK];
	 //prev->next = next;
	//////////////PUSH
	//on se met sur le top de la stack free
	if (ssb->ifree > 0)
	{
		ssb->ifree -= 1;
		index_node = ssb->free[ssb->ifree];
	}
	b[index_node] |= 0x40000000; //in_a
	b[index_node] &= 0xfff003ff; //node.prev = 0 then head.prev
	b[index_node] |= (b[ssb->head] >> INDEX_PREV) & MASK;
	b[ssb->head] &= 0xfff003ff; // head.prev = 0
	b[ssb->head] |= index_node;
	b[index_node] &= 0xfffffc00;// node.next = 0;
	b[index_node] |= ssb->head; // node.next = 0;
	b[index_node] &= 0xc00fffff; //value = 0;
	b[index_node] |= value;
}
/*
DOCUMENTATION DE LA STACK EN BUFFER CIRCULAIRE PSEUDO CHAINEE

*/
