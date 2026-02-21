/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: impinto <impinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:16:07 by impinto           #+#    #+#             */
/*   Updated: 2026/02/21 16:16:58 by impinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

int	parse_value(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (ft_putstr_fd("Error ! Wrong Arguments... [4 - 5]\n", 2), 1);
	if (!parse_value(ac, av))
		return (ft_putstr_fd("Erorr ! Wrong Values... pls reconsider your output.\n",
				2), 1);
}