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

//Valeurs partager:

	//struct : size			:	nb_element actuel
	//struct : head			:	index du top de la stack
	//struct : cap			:	taille du buffer
	//struct : *free		:	list free
	//struct : ifree		:	index en cours de free pour acces O/1

void	ra(t_meta *ssa, t_stack *a)//le premier devient le dernier, move vers le haut
{
	ssa->head = a[ssa->head].next;
}

void	rra(t_meta *ssa, t_stack *a)//le dernier devient le premier, move vers le bas
{
	ssa->head = a[ssa->head].prev ;
}

void	rb(t_meta *ssb, t_stack *b)
{
	ssb->head = b[ssb->head].next;
}

void	rrb(t_meta *ssb, t_stack *b)
{
	ssb->head = b[ssb->head].prev;
}

void	rrr(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	rra(ssa, a);
	rrb(ssb, b);
}

void	rr(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	ra(ssa, a);
	rb(ssb, b);
}

void	sa(t_meta *ssa, t_stack *a)
{
	int	next;
	int	tmp;

	if (ssa->size < 2)
		return ;
	next = (a[ssa->head].next);
	tmp = a[ssa->head].val;
	a[ssa->head].val = a[next].val;
	a[next].val = tmp;
}

void	sb(t_meta *ssb, t_stack *b)
{
	int	next;
	int	tmp;

	if (ssb->size < 2)
		return ;
	next = (b[ssb->head].next);
	tmp = b[ssb->head].val;
	b[ssb->head].val = b[next].val;
	b[next].val = tmp;
}

void	ss(t_meta *ssa, t_meta *ssb, t_stack *b, t_stack *a)
{
	sa(ssa, a);
	sb(ssb, b);
}

void	pa(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	int	value;
	int	index_node;

	value = b[ssb->head].val;
	//pop b push sur a
	ssb->ifree--;
	ssb->free[ssb->ifree] = ssb->head; //on le push dans la liste free
	//on -- first car commence a max_nbr et fini a 0
	b[b[ssb->head].next].prev = b[ssb->head].prev;
	//next->prev = prev;
	b[b[ssb->head].prev].next = b[ssb->head].next;
	//comme on a pop on head = head->next
	ssb->head = b[ssb->head].next;
	ssb->size--;
	//////////////PUSH
	if ((ssa->ifree) >= MAX_NBR)
	{
		write(1, "PA: Attempted to create a new node on a full list.\n", 51);
		exit(1);
	}
	index_node = ssa->free[ssa->ifree++];
	if (ssa->size == 0)//premier noeud allocated
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
	ssa->size++;
}

void	pb(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	int	value;
	int	index_node;

	value = a[ssa->head].val;
	ssa->ifree--;
	ssa->free[ssa->ifree] = ssa->head;
	a[a[ssa->head].next].prev = a[ssa->head].prev;
	a[a[ssa->head].prev].next = a[ssa->head].next;
	ssa->head = a[ssa->head].next;
	ssa->size--;
	if ((ssb->ifree) >= MAX_NBR)
	{
		write(1, "PB: Attempted to create a new node on a full list.\n", 51);
		exit(1);
	}
	index_node = ssb->free[ssb->ifree++];
	if (ssb->size == 0)//premier noeud allocated
	{
		b[index_node].prev = index_node; //- 1 car il n'a pas de noeud voisin
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
