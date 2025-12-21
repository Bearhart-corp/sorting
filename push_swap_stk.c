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
	//struct : *free	:	list free
	//struct : ifree		:	index en cours de free pour acces O/1

//	define:

	//	INDEX_PREV 	0xa
	//	MASK 		0x3ff
	//	VALUE 		0x14
	//	CTRL 		0x1e
	//	IN_A 		1
	//	IN_B 		2
	//	FREE 		0

void	ra(t_meta *ssa, int *a)//le premier devient le dernier, move vers le haut
{
	ssa->head = a[ssa->head] & MASK;	//index du top = top->next
}

void	rra(t_meta *ssa, int *a)//le dernier devient le premier, move vers le bas
{
	ssa->head = a[ssa->head] >> INDEX_PREV & MASK;//index du top = top->prev
}

void	rb(t_meta *ssb, int *b)
{
	ssb->head = b[ssb->head] & MASK;
}

void	rrb(t_meta *ssb, int *b)
{
	ssb->head = b[ssb->head] >> INDEX_PREV & MASK;
}

void	rrr(t_meta *ssa, t_meta *ssb, int *a, int *b)
{
	rra(ssa, a);
	rrb(ssb, b);
}

void	rr(t_meta *ssa, t_meta *ssb, int *a, int *b)
{
	ra(ssa, a);
	rb(ssb, b);
}

void	sa(t_meta *ssa, int *a)
{
	short	next;
	int		tmp;

	if (ssa->size < 2)
		return ;
	next = (a[ssa->head] & MASK); //next = head.next
	tmp = a[ssa->head] & 0x3ff00000; // recup de .value a son index 
	a[ssa->head] = (a[ssa->head] & 0xc00fffff) | (a[next] & 0x3ff00000);
	//head.value = next.value
	a[next] = (a[next] & 0xc00fffff) | tmp;// next.value = .value
}

void	sb(t_meta *ssb, int *b)
{
	short	next;
	int		tmp;

	if (ssb->size < 2)
		return ;
	next = b[ssb->head & MASK];
	tmp = b[ssb->head] & 0x3ff00000; 
	b[ssb->head] = (b[ssb->head] & 0xc00fffff) | (b[next] & 0x3ff00000);
	b[next] = (b[next] & 0xc00fffff) | tmp;
}

void	ss(t_meta *ssa, t_meta *ssb, int *b, int *a)
{
	sa(ssa, a);
	sb(ssb, b);
}

void	pa(t_meta *ssa, t_meta *ssb, int *a, int *b)
{
	int		value;
	short	index_node;

	value = (b[ssb->head] & 0x3ff00000);
	//pop b push sur a
	b[ssb->head] &= 0x3fffffff; // n'est plus utilise dans A ou B (donc free)
	ssb->ifree--;
	ssb->free[ssb->ifree] = ssb->head; //on le push dans la liste free
	//on -- first car commence a max_nbr et fini a 0
	b[b[ssb->head] & MASK] &= 0xfff003ff; // next->prev = 0
	b[b[ssb->head] & MASK] |= ((b[ssb->head] >> INDEX_PREV) & MASK);
	//next->prev = prev;
	b[(b[ssb->head] >> INDEX_PREV) & MASK] &= 0xfffffc00; //prev->next = 0;
	b[(b[ssb->head] >> INDEX_PREV) & MASK] |= b[ssb->head] & MASK;
	//comme on a pop on head = head->next
	ssb->head = b[ssb->head] & MASK;
	ssb->size--;
	//////////////PUSH
	//on se met sur le top de la stack free
	if ((ssa->ifree) >= MAX_NBR)
	{
		write(1, "PA: Attempted to create a new node on a full list.\n", 51);
		exit(1);
	}
	index_node = ssa->free[ssa->ifree];
	ssa->ifree++;
	a[index_node] |= 0x40000000; //in_a
	a[index_node] &= 0xfff003ff; //node.prev = 0 then head.prev
	a[index_node] |= (a[ssa->head] >> INDEX_PREV) & MASK;
	a[ssa->head] &= 0xfff003ff; // head.prev = 0
	a[ssa->head] |= index_node;
	a[index_node] &= 0xfffffc00; // node.next = 0;
	a[index_node] |= ssa->head; // node.next = 0;
	a[index_node] &= 0xc00fffff; //value = 0;
	a[index_node] |= value;
	ssa->head = index_node;
	ssa->size++;
}

void	pb(t_meta *ssa, t_meta *ssb, int *a, int *b)
{
	int		value;
	short	index_node;

	value = (a[ssa->head] & 0x3ff00000);
	a[ssa->head] &= 0x3fffffff; // n'est plus utilise dans A ou B (donc free)
	ssa->ifree--;
	ssa->free[ssa->ifree] = ssa->head; //on le push dans la liste free
	a[a[ssa->head] & MASK] &= 0xfff003ff; // next->prev = 0
	a[a[ssa->head] & MASK] |= ((a[ssa->head] >> INDEX_PREV) & MASK);
	//next->prev = prev;
	a[(a[ssa->head] >> INDEX_PREV) & MASK] &= 0xfffffc00; //prev->next = 0;
	a[(a[ssb->head] >> INDEX_PREV) & MASK] |= a[ssa->head] & MASK;
	ssa->head = a[ssa->head] & MASK;
	ssa->size--;
	 //prev->next = next;
	//////////////PUSH
	//on se met sur le top de la stack free
	if ((ssb->ifree) >= MAX_NBR)
	{
		write(1, "PB: Attempted to create a new node on a full list.\n", 51);
		exit(1);
	}
	index_node = ssb->free[ssb->ifree];
	ssb->ifree += 1;
	b[index_node] |= 0x40000000; //in_a
	b[index_node] &= 0xfff003ff; //node.prev = 0 then head.prev
	b[index_node] |= (b[ssb->head] >> INDEX_PREV) & MASK;
	b[ssb->head] &= 0xfff003ff; // head.prev = 0
	b[ssb->head] |= index_node;
	b[index_node] &= 0xfffffc00;// node.next = 0;
	b[index_node] |= ssb->head; // node.next = 0;
	b[index_node] &= 0xc00fffff; //value = 0;
	b[index_node] |= value;
	ssb->head = index_node;	//tete pointe sur le noeud cree
	ssb->size++;
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
*/
