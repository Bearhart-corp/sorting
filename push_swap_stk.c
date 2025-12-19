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

void	ra(t_meta sa, int *a)//le premier devient le dernier, move vers le haut
{
	sa.head = a[sa.head & MASK];
}

void	rra(t_meta sa, int *a)//le dernier devient le premier, move vers le bas
{
	sa.head = a[(sa.head >> INDEX_PREV)& MASK];
}

void	pa(t_meta *sa, t_meta *sb, int *a, int *b)
{
	short	value;

	value = ((b[sb->head] >> VALUE) & MASK);
	//pop b push sur a
	if (sb->size > 0)
	{
		b[sb->head] &= 0x3fffffff; // n'est plus utilise dans A ou B (donc free)
		sb->free[sb->ifree++] = sb->head; //on le push dans la liste free
		//celui avant doit pointer vers celui apres et celui apres avant
		b[b[sb->head] & MASK] &= 0xfff003ff;
		b[b[sb->head] & MASK] |= ((b[sb->head] >> INDEX_PREV) & MASK);
		b[((b[sb->head] >> INDEX_PREV) & MASK)] = (b[sb->head] & MASK);
		
	}
	else 
		return (write(1, "error", 5));
}

void	pb(t_meta sa, t_meta sb, int *a, int *b)
{
	if (sa.size > 0)
	{

	}
}
/*
DOCUMENTATION DE LA STACK EN BUFFER CIRCULAIRE PSEUDO CHAINEE

*/
