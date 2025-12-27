/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaboure <etaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 09:59:44 by etaboure          #+#    #+#             */
/*   Updated: 2025/12/27 18:07:54 by etaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GNL/get_next_line.h"
#include "checker.h"
#include <fcntl.h>

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
	ssa->size = (size_t)n_elem; 				//full
	ssb->size = 0; 								//vide
	ssa->head = (size_t)(MAX_NBR - n_elem);		//TOP STACK verif que c 504
	ssb->head = (size_t)MAX_NBR - 1;				//tout en bas
	ssa->ifree = MAX_NBR;	// a verifier depassement
	ssb->ifree = 0;				//FULL et commence a 511
	while (ssb->ifree < MAX_NBR)
	{
		ssb->free[ssb->ifree] = ssb->ifree;
		ssb->ifree++;
	}
	ssb->ifree = 0; //full donc index sur le top de la stack
}

static int	ft_still_number(char *s)
{
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			return (1);
		s++;
	}
	return (0);
}

static int	ft_atoi(char **s_ptr, char *s, int base)
{
	int		sign;
	int		acc;

	if (base > 10 || base < 2 || !s)
		return (0);
	sign = -1;
	acc = 0;
	while (*s == 32 && *s && (*s >= 8 || *s <= 13))
		s++;
	while (*s && (*s == '+' || *s == '-'))
	{
		if (*s == '-')
			sign = 1;
		s++;
	}
	while (*s && (*s >= '0' && *s <= '9'))//base <= 10 accepted
		acc = acc * base - (*s++ - 48);
	*s_ptr = s;
	return (acc * sign);
}

int	full_stack_b(char **argv, int argc, int n_elem, t_stack *b)
{
	int	i;
	
	i = 0;
	while (++i < argc)
	{
		while (*argv[i]) //on rempli tab des nbr passe en param
		{
			if (ft_still_number(argv[i]))
				b[n_elem++].val = ft_atoi(&argv[i], argv[i], 10);
			else
				break ;
		}
	}
	return (n_elem);
}

int	sort(char **sort_instr)
{
	int	i;

	i = 0;
	while (sort_instr[i])
	{
		if (ft_strstr(sort_instr[i], "pb"))
			printf("exec pb\n");
		if (ft_strstr(sort_instr[i], "pa"))
			printf("exec pa\n");
		if (ft_strstr(sort_instr[i], "ss"))
			printf("exec ss\n");
		if (ft_strstr(sort_instr[i], "sb"))
			printf("exec sb\n");
		if (ft_strstr(sort_instr[i], "sa"))
			printf("exec sa\n");
		if (ft_strstr(sort_instr[i], "rr"))
			printf("exec rr\n");
		if (ft_strstr(sort_instr[i], "rrr"))
			printf("exec rrr\n");
		if (ft_strstr(sort_instr[i], "rrb"))
			printf("exec rrb\n");
		if (ft_strstr(sort_instr[i], "rb"))
			printf("exec rb\n");
		if (ft_strstr(sort_instr[i], "rra"))
			printf("exec rra\n");
		if (ft_strstr(sort_instr[i], "ra"))
			printf("exec ra\n");
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	char	*sort_instr[0x3000]; /*faut faire des bon algo (au pire on tente le define)*/
	int		k;
	t_stack a[MAX_NBR];
	t_stack b[MAX_NBR];
	t_meta	ssa;
	t_meta	ssb; //meta donnees sur les stacks. head et size
	int		n_elem; //nbr reel
	int 	i;
	int 	j;
	int		t;
	int 	count;
	char	seen[MAX_NBR];

	i = 0;
	t = 0;
	n_elem = 0;
	n_elem = full_stack_b(argv, argc, n_elem, b);
	init_meta_data(&ssa, &ssb, n_elem);
	i = 0;
	while (i < n_elem)
		seen[i++] = 0;
	i = n_elem;
	while (--i >= 0)
	{
		count = 0;
		j = 0;
		while (j < n_elem)
			if (b[i].val > b[j++].val)
				count++;
		if (seen[count])
			return (write(1, "error", 5));
		seen[count] = 1;
		a[MAX_NBR - 1 - t++].val = count;
	}
	i = MAX_NBR;
	init(n_elem, a, b);
	k = 0;
	// if (argc == 1)
	// 	return (0);
	sort_instr[k] = get_next_line(0);
	while (sort_instr[k])
		sort_instr[++k] = get_next_line(0);
	sort_instr[k] = 0;
	if (sort(sort_instr) == 0)
		printf("OK");
	else
		printf("KO");
	return (0);
}
