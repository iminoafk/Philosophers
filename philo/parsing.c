/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: impinto <impinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:34:30 by impinto           #+#    #+#             */
/*   Updated: 2026/08/11 16:54:57 by impinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <limits.h>

int	ft_atoi(const char *s)
{
	long	res;
	int		i;

	i = 0;
	res = 0;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			return (0);
		i++;
	}
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		res = res * 10 + (s[i] - '0');
		if (res > INT_MAX)
			return (0);
		i++;
	}
	return ((int)res);
}
