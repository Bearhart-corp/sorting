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
		if (!(*s >= '0' && *s <= '9'))
			s++;
		else
			return (1);
	}
	return (0);
}

int	ft_atoi(char **s_ptr, char *s, int base)
{
	int		sign;
	int		acc;

	if ((base > 10 && base < 2 )|| !s)
		return (0);
	sign = 1;
	acc = 0;
	while (*s == 32 && *s && (*s >= 8 || *s <= 13))
		s++;
	while (*s && *s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s && (*s >= '0' && *s <= '9' ))//base < 10 accepted
		acc = acc * base + ("0123456789"[*s++ - 48] - 48);
	*s_ptr = s;
	return (acc * sign);
}

int main(int ac, char **av)
{
	int		tab[MAX_NUMBER_TO_SORT];//max = 512 car on trie pas plus de 500nbr
	int		n_elem; //nbr reel
	t_ring	a;
	t_ring	b;

	if (ac > 2)
		return (write(1, "huele a concha chico", 20)); //error
	n_elem = 0;
	while (*av[1]) //on rempli tab des nbr passe en param
	{
		if (ft_still_number(av[1]))
			tab[n_elem++] = ft_atoi(&av[1], av[1], 10);
		else
			break ;
	}
	init(&a, n_elem, tab); //malloc de la stack A
	init(&b, n_elem, NULL);//pareil pour B mais sans elem donc elle est vide.

	///////////////test de l'init de la stack
	for (int i = 0; i < n_elem; ++i)
		printf("%d\n", a.ring[i]);
}