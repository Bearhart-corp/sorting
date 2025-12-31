/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <tbelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 13:09:37 by tbelard           #+#    #+#             */
/*   Updated: 2025/12/28 17:08:09 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	up_or_down(t_meta ssa, t_meta ssb, t_stack *a, t_stack *b)
{
	short	count;

	if (ssa.flag == 'a')
	{
		while (a[ssa.head].val != ssa.target)
		{
			count++;
			ssa.head = a[ssa.head].next;
		}
		return (count >= (ssa.size / 2));//rra = 1
	}
	else
	{
		while (b[ssb.head].val != ssa.target)
		{
			count++;
			ssb.head = b[ssb.head].next;
		}
		return (count >= (ssb.size / 2));
	}
}

void	init(int n_elem, t_stack *a, t_stack *b)
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
	i = 0;
	while (i < n_elem)
		b[i++].val = 0;
}

void	init_meta_data(t_meta *ssa, t_meta *ssb, int n_elem)
{
	ssa->size = (size_t)n_elem;
	ssa->n = (size_t)n_elem;
	ssb->size = 0;
	ssa->head = (size_t)(MAX_NBR - n_elem);
	ssb->head = (size_t)MAX_NBR - 1;
	ssa->ifree = MAX_NBR;
	ssb->ifree = 0;	
	while (ssb->ifree < MAX_NBR)
	{
		ssb->free[ssb->ifree] = ssb->ifree;
		ssb->ifree++;
	}
	ssb->ifree = 0;
}

void	ft_push_swap(t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	//cette fonction sert a rediriger vers le bon algo en fonction
	//du flag lors de la compil ou du % de desordre
	if (ssa->size < 4)
	{
		algo_2move(ssa, a);
		ssa->start_l = ssa->head;
	}
	else
	{
		quick_turk(ssa, ssb, a, b);
		//cocktail(ssa, ssb, a, b);
	}
	ssa->start_l = ssa->head;
	printf("\n\tcost: %zu\n", ssa->count);
	ft_print_stack(*ssa, *ssb, a, b);
}
/*
#!/bin/bash

# Nombre total de nombres
total=500

# Pourcentage de désordre (ici 15%)
disorder_count=75  # 15% de 500 est 75

# Générer une liste ordonnée de nombres
seq 1 $total > list.txt

# Mélanger 75 nombres
shuf -n $disorder_count list.txt > disorder.txt

# Conserver le reste dans l'ordre
head -n $((total - disorder_count)) list.txt > ordered.txt

# Combiner les listes mélangées et ordonnées
cat disorder.txt ordered.txt > final_list.txt

# Afficher la liste finale
cat final_list.txt
*/