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
	sa.head = a[sa.head & MASK];//index du top = top->next
}

void	rra(t_meta sa, int *a)//le dernier devient le premier, move vers le bas
{
	sa.head = a[(sa.head >> INDEX_PREV)& MASK];//index du top = top->prev
}

void	rb(t_meta sb, int *b)
{
	sb.head = b[sb.head & MASK];
}

void	rrb(t_meta sb, int *b)
{
	sb.head = b[(sb.head >> INDEX_PREV)& MASK];
}

void	rrr(t_meta sa, t_meta sb, int *a, int *b)
{
	rra(sa, a);
	rrb(sb, b);
}

void	rr(t_meta sa, t_meta sb, int *a, int *b)
{
	ra(sa, a);
	rb(sb, b);
}

void	sa(t_meta sa, int *a)
{
	short	next;
	int		tmp;

	if (sa.size < 2)
		return ;
	next = a[sa.head & MASK]; //next = head.next
	if (a[sa.head] == a[next])
		return ;
	tmp = a[sa.head] & 0x3ff00000; // recup de .value a son index 
	a[sa.head] = (a[sa.head] & 0xc00fffff) | (next & 0x3ff00000);
	//head.value = next.value
	a[next] = (a[next] & 0xc00fffff) | tmp;// next.value = .value
}

void	sb(t_meta sb, int *b)
{
	short	next;
	int		tmp;

	if (sb.size < 2)
		return ;
	next = b[sb.head & MASK];
	if (b[sb.head] == b[next])
		return ;
	tmp = b[sb.head] & 0x3ff00000; 
	b[sb.head] = (b[sb.head] & 0xc00fffff) | (next & 0x3ff00000);
	b[next] = (b[next] & 0xc00fffff) | tmp;
}

void	ss(t_meta sa, t_meta sb, int *b, int *a)
{
	sa(sa, a);
	sb(sb, b);
}

void	pa(t_meta *sa, t_meta *sb, int *a, int *b)
{
	short	value;
	short	index_node;

	value = (b[sb->head] & 0x3ff00000);
	//pop b push sur a
	b[sb->head] &= 0x3fffffff; // n'est plus utilise dans A ou B (donc free)
	sb->free[sb->ifree++] = sb->head; //on le push dans la liste free

	b[b[sb->head] & MASK] &= 0xfff003ff; // next->prev = 0
	b[b[sb->head] & MASK] |= ((b[sb->head] >> INDEX_PREV) & MASK)
	//next->prev = prev;
	b[(b[sb->head] >> INDEX_PREV) & MASK] &= 0xfffffc00; //prev->next = 0;
	b[(b[sb->head] >> INDEX_PREV) & MASK] |= b[b[sb->head] & MASK];
	 //prev->next = next;
	//////////////PUSH
	//on se met sur le top de la stack free
	if (sa.ifree > 0)
		index_node = sa->free[sa->--ifree];
	a[index_node] |= 0x40000000; //in_a
	a[index_node] &= 0xfff003ff; //node.prev = 0 then head.prev
	a[index_node] |= (a[sa->head] >> INDEX_PREV) & MASK;
	a[sa->head] &= 0xfff003ff; // head.prev = 0
	a[sa->head] |= index_node;
	a[index_node] &= 0xfffffc00 // node.next = 0;
	a[index_node] |= sa->head; // node.next = 0;
	a[index_node] &= 0xc00fffff; //value = 0;
	a[index_node] |= value;
}

void	pb(t_meta sa, t_meta sb, int *a, int *b)
{
	short	value;
	short	index_node;

	value = (b[sb->head] & 0x3ff00000);
	//pop b push sur a
	a[sa->head] &= 0x3fffffff; // n'est plus utilise dans A ou B (donc free)
	sa->free[sa->ifree++] = sa->head; //on le push dans la liste free
	//celui avant doit pointer vers celui apres et celui apres avant

	a[a[sa->head] & MASK] &= 0xfff003ff; // next->prev = 0
	a[a[sa->head] & MASK] |= ((a[sa->head] >> INDEX_PREV) & MASK)
	//next->prev = prev;
	a[((a[sa->head] >> INDEX_PREV) & MASK)] &= 0xfffffc00; //prev->next = 0;
	a[((a[sb->head] >> INDEX_PREV) & MASK)] |= a[a[sa->head] & MASK];
	 //prev->next = next;
	//////////////PUSH
	//on se met sur le top de la stack free
	if (sb.ifree > 0)
		index_node = sb->free[sb->--ifree];
	b[index_node] |= 0x40000000; //in_a
	b[index_node] &= 0xfff003ff; //node.prev = 0 then head.prev
	b[index_node] |= (b[sb->head] >> INDEX_PREV) & MASK;
	b[sb->head] &= 0xfff003ff; // head.prev = 0
	b[sb->head] |= index_node;
	b[index_node] &= 0xfffffc00 // node.next = 0;
	b[index_node] |= sb->head; // node.next = 0;
	b[index_node] &= 0xc00fffff; //value = 0;
	b[index_node] |= value;
}
/*
DOCUMENTATION DE LA STACK EN BUFFER CIRCULAIRE PSEUDO CHAINEE

*/
