/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaboure <etaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 17:37:18 by etaboure          #+#    #+#             */
/*   Updated: 2025/12/28 18:01:10 by etaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	ft_strcmp( char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] && s2[i]) && (s1[i] == s2[i]))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

int	not_sorted(t_meta ssa, t_meta ssb, t_stack *a, t_stack *b)
{
	int i;

	i = 0;
	while (ssa.size-- > 1)
	{
		if (a[ssa.head].val > a[a[ssa.head].next].val)
			i = 1;
		ssa.head = a[ssa.head].next;
	}
	while (ssb.size-- > 1)
	{
		if (b[ssb.head].val < b[b[ssb.head].next].val)
			i = 1;
		ssb.head = b[ssb.head].next;
	}
	return (i); //0 = is sorted
}