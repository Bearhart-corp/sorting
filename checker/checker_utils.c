/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaboure <etaboure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 17:37:18 by etaboure          #+#    #+#             */
/*   Updated: 2025/12/27 17:38:16 by etaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;
	int	size_to_find;

	j = 0;
	i = 0;
	size_to_find = 0;
	if (!to_find)
		return (str);
	while (to_find[size_to_find])
		size_to_find++;
	while (str[i])
	{
		j = 0;
		while (str[i + j] == to_find[j] && str[i + j])
		{
			j++;
			if (to_find[j] == '\0')
				return (&str[i]);
		}
		i++;
	}
	return (0);
}