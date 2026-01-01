/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_stk.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <tbelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:25:17 by tbelard           #+#    #+#             */
/*   Updated: 2025/12/28 17:06:51 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	ra(t_meta *ssa, t_stack *a)
{
	ssa->head = a[ssa->head].next;
	if (ssa->double_op == 0)
		printf("ra\n");
	return (1);
}

size_t	rra(t_meta *ssa, t_stack *a)
{
	ssa->head = a[ssa->head].prev ;
	if (ssa->double_op == 0)
		printf("rra\n");
	return (1);
}

size_t	rb(t_meta *ssb, t_stack *b)
{
	ssb->head = b[ssb->head].next;
	if (ssb->double_op == 0)
		printf("rb\n");
	return (1);
}

size_t	rrb(t_meta *ssb, t_stack *b)
{
	ssb->head = b[ssb->head].prev;
	if (ssb->double_op == 0)
		printf("rrb\n");
	return (1);
}

size_t	rrr(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	ssa->double_op = 1;
	ssb->double_op = 1;
	rra(ssa, a);
	rrb(ssb, b);
	ssa->double_op = 0;
	ssb->double_op = 0;
	printf("rrr\n");
	return (1);
}

size_t	rr(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	ssa->double_op = 1;
	ssb->double_op = 1;
	ra(ssa, a);
	rb(ssb, b);
	ssa->double_op = 0;
	ssb->double_op = 0;
	printf("rr\n");
	return (1);
}

size_t	sa(t_meta *ssa, t_stack *a)
{
	int	next;
	int	tmp;

	if (ssa->size < 2)
		return (0);
	next = (a[ssa->head].next);
	tmp = a[ssa->head].val;
	a[ssa->head].val = a[next].val;
	a[next].val = tmp;
	if (ssa->double_op == 0)
		printf("sa\n");
	return (1);
	
}

size_t	sb(t_meta *ssb, t_stack *b)
{
	int	next;
	int	tmp;

	if (ssb->size < 2)
		return (0);
	next = (b[ssb->head].next);
	tmp = b[ssb->head].val;
	b[ssb->head].val = b[next].val;
	b[next].val = tmp;
	if (ssb->double_op == 0)
		printf("sb\n");
	return (1);

}

size_t	ss(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	ssa->double_op = 1;
	ssb->double_op = 1;
	sa(ssa, a);
	sb(ssb, b);
	ssa->double_op = 0;
	ssb->double_op = 0;
	printf("ss\n");
	return (1);
}

size_t	pa(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	int	value;
	int	index_node;

	value = b[ssb->head].val;
	ssb->free[--ssb->ifree] = ssb->head;
	b[b[ssb->head].next].prev = b[ssb->head].prev;// a->next->prev = head
	b[b[ssb->head].prev].next = b[ssb->head].next;
	ssb->head = b[ssb->head].next;
	ssb->size--;
	if ((ssa->ifree) >= MAX_NBR)
		exit(1);
	index_node = ssa->free[ssa->ifree++];
	if (ssa->size++ == 0)//premier noeud allocated
	{
		a[index_node].prev = index_node; //- 1 car il n'a pas de noeud voisin
		a[index_node].next = index_node;
		ssa->head = index_node;
	}
	else
	{
		a[index_node].next = ssa->head;
		a[index_node].prev = a[ssa->head].prev;
		a[ssa->head].prev =	index_node;
		ssa->head = index_node;
		a[a[index_node].prev].next = index_node;
	}
	a[index_node].val = value;
	printf("pa\n");
	return (1);
}

size_t	pb(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	int	value;
	int	index_node;

	value = a[ssa->head].val;
	ssa->free[--ssa->ifree] = ssa->head;
	a[a[ssa->head].next].prev = a[ssa->head].prev;
	a[a[ssa->head].prev].next = a[ssa->head].next;
	ssa->head = a[ssa->head].next;
	ssa->size--;
	if ((ssb->ifree) >= MAX_NBR)
		exit(1);
	index_node = ssb->free[ssb->ifree++];
	if (ssb->size++ == 0)
	{
		b[index_node].prev = index_node;
		b[index_node].next = index_node;
		ssb->head = index_node;
	}
	else
	{
		b[index_node].next = ssb->head;
		b[index_node].prev = b[ssb->head].prev;
		b[ssb->head].prev =	index_node;
		ssb->head = index_node;
		b[b[index_node].prev].next = index_node;
	}
	b[index_node].val = value;
	printf("pb\n");
	return (1);
}
/*
DOCUMENTATION DE LA STACK EN BUFFER CIRCULAIRE PSEUDO CHAINEE


la stack free commence tout en haut a 0 et monte en faisant ++
quand on pop une valeur de la liste pour allouer un nouveau noeud
on decremente juste avant, si on push on ++ le head de la stack apres avoir
desallouer, donc si il m'y a rien dans la liste comme c'est le cas au debut avec 
A car elle est 100% allouer, la tete de lecture pointe sur l'index 0
si on push sur B alors on dessaloue sur A et on ajoute la valeur a 
l'index 0 puis on ++ la tete.
du coup quand on pop et qu'on veut allouer un nouveau noeud on 
-- la tete de lecture pour revenir a 0 dans cet exemple et on recupere la valeur
puis on peut repeter l'operation autant de * que necessaire. 


SWAP DE POINTER AU LIEU DE VALEUR

int	next;
	int	prev;

	if (ssb->size < 2)
		return ;
	next = (b[ssb->head].next);
	prev = (b[ssb->head].prev);
	b[prev].next = b[ssb->head].next;
	b[next].prev = b[ssb->head].prev;
	b[ssb->head].prev = next;
	b[ssb->head].next = b[next].next;
	b[next].next = ssb->head;
*/
