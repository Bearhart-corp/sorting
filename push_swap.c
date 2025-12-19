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

int	ft_atoi(char **s_ptr, char *s, int base)
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
	int		b[MAX_NUMBER_TO_SORT];//max = 512 car on trie pas plus de 500nbr
	int		a[MAX_NUMBER_TO_SORT];
	int		n_elem; //nbr reel
	int 	i = 0;
	int 	j;
	int 	count;
	t_meta	a;
	t_meta	b; //meta donnees sur les stacks. head et size

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
	a.size = n_elem; //full
	b.size = 0; //vide
	a.head = 0;	//tout en haut
	b.head = (n_elem - 1); //tout en bas
	a.cap = b.cap = n_elem;
	
	i = 0;
	while (i < n_elem)//doublons non traites. mais sorted after anyway..
	{
		count = 0;
		j = 0;
		while (j < n_elem)
			if (b[i] > b[j++])
				count++;
		a[i] = count;
		i++;
	}
	init(n_elem, a);
	i = 0;
	while (i < n_elem)
		printf("%d\n", a[i++]);
	i = 0;
	while (i < n_elem)
		b[i++] = 0;
}
// 12 1 24 5 16
// 2  0  4 1  3
// 1  5  12 16 24

/// https://github.com/alx-sch/push_swap

