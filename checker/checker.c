/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaboure <etaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 09:59:44 by etaboure          #+#    #+#             */
/*   Updated: 2025/12/28 16:57:57 by etaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GNL/get_next_line.h"
#include "checker.h"
#include <fcntl.h>

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

int	sort(char **sort_instr, t_meta *ssa, t_meta *ssb, t_stack *a, t_stack *b)
{
	int	i;

	i = 0;
	while (sort_instr[i])
	{
		if (ft_strstr(sort_instr[i], "pb"))
			pb(ssa, ssb, a, b);
		if (ft_strstr(sort_instr[i], "pa"))
			pa(ssa, ssb, a, b);
		if (ft_strstr(sort_instr[i], "ss"))
			ss(ssa, ssb, a, b);
		if (ft_strstr(sort_instr[i], "sb"))
			sb(ssb, b);
		if (ft_strstr(sort_instr[i], "sa"))
			sa(ssa, a);
		if (ft_strstr(sort_instr[i], "rr"))
			rr(ssa, ssb, a, b);
		if (ft_strstr(sort_instr[i], "rrr"))
			rrr(ssa, ssb, a, b);
		if (ft_strstr(sort_instr[i], "rrb"))
			rrb(ssb, b);
		if (ft_strstr(sort_instr[i], "rb"))
			rb(ssb, b)
;		if (ft_strstr(sort_instr[i], "rra"))
			rra(ssa, a);
		if (ft_strstr(sort_instr[i], "ra"))
			ra(ssa, a);
		i++;
	}
	printf("head : %zu\n",ssb->head);
	printf("si 0 dans l'ordre : %d\n", isNot_sorted(*ssa, *ssb, a, b));
	if (isNot_sorted(*ssa, *ssb, a, b))
		return (1);
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
	if (!(sort(sort_instr, &ssa, &ssb, a, b)))
		printf("OK");
	else
		printf("KO");
	return (0);
}
