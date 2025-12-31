/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <tbelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 12:35:43 by tbelard           #+#    #+#             */
/*   Updated: 2025/12/28 17:05:53 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <time.h>

static int normalizator(t_main *s, int n_elem, t_stack *a, t_stack *b)
{
	s->i = n_elem;
	s->t = 0;
	while (--s->i >= 0)
	{
		s->count = 0;
		s->j = 0;
		while (s->j < n_elem)
			if (b[s->i].val > b[s->j++].val)
				s->count++;
		if (s->seen[s->count])
			return (1);
		s->seen[s->count] = 1;
		a[MAX_NBR - 1 - s->t++].val = s->count;
	}
	s->i = MAX_NBR;
	return (0);
}

static long fonct(t_main s, t_stack *b, int ac, char **av)
{
	int n_elem;

	n_elem = 0;
	s.i = MAX_NBR;
	while (--s.i)
		s.seen[s.i] = 0;
	s.i = 0;
	while (++s.i < ac)
	{
		while (*av[s.i]) //on rempli tab des nbr passe en param
		{
			if (ft_still_number(av[s.i]))
			{
				s.sentinel = ft_atoi(&av[s.i], av[s.i], 10);
				if (s.sentinel == 0xffffffffffffffff)
					return (0xffffffffffffffff);
				else
					b[n_elem++].val = (int)s.sentinel;
			}
			else
				break ;
		}
	}
	return (n_elem);
}

int main(int ac, char **av)
{
	t_stack	b[MAX_NBR];//max = 512 car on trie pas plus de 500nbr
	t_stack	a[MAX_NBR];
	t_meta	ssa;
	t_meta	ssb; //meta donnees sur les stacks. head et size
	int		n_elem; //nbr reel
	t_main	s;

	n_elem = fonct(s, b, ac, av);
	if (n_elem == 0xffffffffffffffff)
		return (write(1, "error", 5));
	init_meta_data(&ssa, &ssb, n_elem);
	if (normalizator(&s, n_elem, a, b))
		return (write(1, "error", 5));
	init(n_elem, a, b);
	ft_push_swap(&ssa, &ssb, a, b);
}
