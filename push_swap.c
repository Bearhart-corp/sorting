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
	int		b[MAX_NBR];//max = 512 car on trie pas plus de 500nbr
	int		a[MAX_NBR];
	int		n_elem; //nbr reel
	int 	i = 0;
	int 	j;
	int		t;
	int 	count;
	char	seen[MAX_NBR];
	t_meta	ssa;
	t_meta	ssb; //meta donnees sur les stacks. head et size

	n_elem = 0;
	while (++i < ac)
	{
		while (*av[i]) //on rempli tab des nbr passe en param
		{
			if (ft_still_number(av[i]))
				b[n_elem++] = ft_atoi(&av[i], av[i], 10);
			else
				break ;
		}
	}
	///init struct
	ssa.size = (size_t)n_elem; //full
	ssb.size = 0; //vide
	ssa.head = 0;	//tout en haut
	ssb.head = (size_t)(n_elem - 1); //tout en bas
	ssa.cap = ssb.cap = (size_t)n_elem;
	ssa.ifree = ssb.ifree = 0;
	
	i = 0;
	while (i < n_elem)
		seen[i++] = 0;
	i = n_elem;
	t = 0;
	while (--i >= 0)//doublons non traites.
	{
		count = 0;
		j = 0;
		while (j < n_elem)
			if (b[i] > b[j++])
				count++;
		if (seen[count])
			return (write(1, "error", 5));
		seen[count] = 1;
		a[MAX_NBR - 1 - t++] = count;
	}
	
	i = MAX_NBR; t = 0;
	init(n_elem, a);
	while (t++ < n_elem)
		printf("%d, ", a[MAX_NBR - t]);
	i = 0;
	while (i < n_elem)
		b[i++] = 0;
	ft_push_swap(ssa, ssb, a, b);
}

//commentaire l'init semble fonctionner
//stack commence bien a partir de la fin,le premier elem
//au'on nous donne devient bien le top de la stack

/// https://github.com/alx-sch/push_swap
/*
1078459897:	4	01|00.0000.0100|0111.1111.11|01.1111.1001	504
1074258426:	0	01|00.0000.0000|0111.1110.00|01.1111.1010	505
1080550907:	6	01|00.0000.0110|0111.1110.01|01.1111.1011	506
1076357628:	2	01|00.0000.0010|0111.1110.10|01.1111.1100	507
1079504381:	5	01|00.0000.0101|0111.1110.11|01.1111.1101	508
1075311102:	1	01|00.0000.0001|0111.1111.00|01.1111.1110	509
1081603583:	7	01|00.0000.0111|0111.1111.01|01.1111.1111	510
1077410296:	3	01|00.0000.0011|0111.1111.10|01.1111.1000	511

				01|00.0000.0000|0000.0011.10|00.0000.0011
*/