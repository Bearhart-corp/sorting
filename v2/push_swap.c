/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 12:35:43 by tbelard           #+#    #+#             */
/*   Updated: 2025/12/14 12:35:45 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

	if ((base > 10 && base < 2 )|| !s)
		return (0);
	sign = -1;
	acc = 0;
	while (*s == 32 && *s && (*s >= 8 || *s <= 13))
		s++;
	while (*s && *s == '+' || *s == '-')
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

int main(int ac, char **av)
{
	t_stack	b[MAX_NBR];//max = 512 car on trie pas plus de 500nbr
	t_stack	a[MAX_NBR];
	t_meta	ssa;
	t_meta	ssb; //meta donnees sur les stacks. head et size
	int		n_elem; //nbr reel
	int 	i;
	int 	j;
	int		t;
	int 	count;
	char	seen[MAX_NBR];

	i = 0;
	n_elem = 0;
	while (++i < ac)
	{
		while (*av[i]) //on rempli tab des nbr passe en param
		{
			if (ft_still_number(av[i]))
				b[n_elem++].val = ft_atoi(&av[i], av[i], 10);
			else
				break ;
		}
	}
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
	
	printf("\t\tCHECK DE LA NORMALISATION\n\n");
	printf("BOTTOM, ");
	for (t = 0; t < n_elem;)
		printf("%d, ", (a[MAX_NBR - 1 - t++].val));
	printf("TOP");
	printf("\n______________________\n\n");

	init(n_elem, a);
	printf("\n\n\tCHECK DE L'INIT\n\n");
	for (t = 0; t < n_elem; t++ )
	{
		printf("\t[%d]", MAX_NBR - n_elem + t);
		printf("\t Value = %d", (a[MAX_NBR - n_elem + t].val));
		printf("\t Prev = %hd", (a[MAX_NBR - n_elem + t].prev));
		printf("\t Next = %hd\n", (a[MAX_NBR - n_elem + t].next));
	}
	printf("\n______________________\n");
	
	i = 0;
	while (i < n_elem)
		b[i++].val = 0;
	ft_push_swap(&ssa, &ssb, a, b);//here we assign A to by the sorted one
}

/// https://github.com/alx-sch/push_swap
