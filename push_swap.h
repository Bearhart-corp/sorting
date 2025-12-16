/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 13:10:00 by tbelard           #+#    #+#             */
/*   Updated: 2025/12/14 13:10:03 by tbelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# define MAX_NUMBER_TO_SORT 0x200

typedef struct s_ring
{
	int	*ring;
	int	top_phys;
	int	n;
	int	size;
	int	top_logik;
}	t_ring;

void	init(t_ring *stk, int n_elem, int *tab);
int		push(t_ring *r);
int		pop(t_ring *r);
void	rra(t_ring *r);
void	ra(t_ring *r);
void	*ft_memcpy(void *dest, const void *src, size_t n_byte);

#endif
