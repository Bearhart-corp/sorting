/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaboure <etaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 14:39:45 by etaboure          #+#    #+#             */
/*   Updated: 2025/12/28 18:01:49 by etaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "../v3/push_swap.h"

# ifndef NB_ARG
#  define NB_ARG 0x3000
# endif

// helper
int		ft_strcmp( char *s1, char *s2);
int		not_sorted(t_meta ssa, t_meta ssb, t_stack *a, t_stack *b);

#endif