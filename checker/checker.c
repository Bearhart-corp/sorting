/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaboure <etaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 09:59:44 by etaboure          #+#    #+#             */
/*   Updated: 2025/12/28 18:09:53 by etaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GNL/get_next_line.h"
#include "checker.h"
#include <fcntl.h>

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
	printf("head debut : %zu\n", ssa->head);
	while (sort_instr[i])
	{
		if (ft_strcmp(sort_instr[i], "pb\n") == 0)
			pb(ssa, ssb, a, b);
		else if (ft_strcmp(sort_instr[i], "pa\n") == 0)
			pa(ssa, ssb, a, b);
		else if (ft_strcmp(sort_instr[i], "ss\n") == 0)
			ss(ssa, ssb, a, b);
		else if (ft_strcmp(sort_instr[i], "sb\n") == 0)
			sb(ssb, b);
		else if (ft_strcmp(sort_instr[i], "sa\n") == 0)
			sa(ssa, a);
		else if (ft_strcmp(sort_instr[i], "rr\n") == 0)
			rr(ssa, ssb, a, b);
		else if (ft_strcmp(sort_instr[i], "rrr\n") == 0)
			rrr(ssa, ssb, a, b);
		else if (ft_strcmp(sort_instr[i], "rrb\n") == 0)
			rrb(ssb, b);
		else if (ft_strcmp(sort_instr[i], "rb\n") == 0)
			rb(ssb, b)
;		else if (ft_strcmp(sort_instr[i], "rra\n") == 0)
			rra(ssa, a);
		else if (ft_strcmp(sort_instr[i], "ra\n") == 0)
			ra(ssa, a);
		i++;
	}
	printf("head fin : %zu\n", ssa->head);
	if (not_sorted(*ssa, *ssb, a, b))
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
