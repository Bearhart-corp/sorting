/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <tbelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 14:46:13 by tbelard           #+#    #+#             */
/*   Updated: 2025/12/28 17:06:17 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

float	desorder(t_meta ssa, t_meta ssb, t_stack *a, t_stack *b)
{
	float 	mistake;
	float	total_pairs;
	int		i;
	int		j;

	i = ssa.head;
	ssa.end_l = a[i].prev;
	mistake = 0;
	total_pairs = 0;
	while (i != ssa.end_l)
	{
		j = a[i].next;
		while (j != ssa.end_l)
		{
			total_pairs++;
			if (a[i].val > a[j].val)
				mistake++;
			j = a[j].next;
		}
		i = a[i].next;
	}
	return (((mistake / total_pairs)));
}

int	isNot_sorted(t_meta ssa, t_meta ssb, t_stack *a, t_stack *b)
{
	int i;

	i = 0;
	while (ssa.size-- > 1)
	{
		if (a[ssa.top_phys].val > a[a[ssa.top_phys].next].val)
			i = 1;
		ssa.top_phys = a[ssa.top_phys].next;
	}
	while (ssb.size-- > 1)
	{
		if (b[ssb.top_phys].val < b[b[ssb.top_phys].next].val)
			i = 1;
		ssb.top_phys = b[ssb.top_phys].next;
	}
	return (i);
}

void	ft_print_stack(t_meta ssa, t_meta ssb, t_stack *a, t_stack *b)
{
	printf("\n\tETAT STACK A\n\n");
	for(int p = 0; p < ssa.size; p++)
	{
		printf("\t[%zu]", ssa.head);
		printf("\t= %d\n" , a[ssa.head].val);
		ssa.head = a[ssa.head].next;
	}
	printf("\n\tETAT STACK B\n\n");
	for(int p = 0; p < ssb.size; p++)
	{
		printf("\t[%zu]", ssb.head);
		printf("\t= %d\n" , b[ssb.head].val);
		ssb.head = b[ssb.head].next;
	}
}

int	ft_still_number(char *s)
{
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			return (1);
		s++;
	}
	return (0);
}

long	ft_atoi(char **s_ptr, char *s, int base)
{
	int		sign;
	int		acc;

	if ((base > 10 || base < 2 ) || !s)
		return (0);
	sign = -1;
	acc = 0;
	while (*s && *s == 32 || (*s >= 8 && *s <= 13))
		s++;
	while (*s && (*s == '+' || *s == '-'))
	{
		if (*s == '-')
			sign = 1;
		s++;
	}
	while (*s && !(*s == 32 || (*s >= 8 && *s <= 13)))//base <= 10 accepted
	{
		if (*s >= '0' && *s <= '9')
			acc = acc * base - (*s++ - 48);
		else
			return ((long)-1);
	}
	*s_ptr = s;
	return (acc * sign);
}
