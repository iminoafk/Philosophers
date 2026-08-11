/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: impinto <impinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:16:07 by impinto           #+#    #+#             */
/*   Updated: 2026/08/11 16:52:50 by impinto          ###   ########.fr       */
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
	t_data	*data;

	if (ac < 5 || ac > 6)
		return (ft_putstr_fd("Error ! Wrong Arguments... [4 - 5]\n", 2), 1);
	if (!parse_value(ac, av))
		return (ft_putstr_fd("Error ! Wrong Values...\n", 2), 1);
	data = fill_data_struct(ac, av);
	if (!data)
		return (ft_putstr_fd("Error ! Initialization failed.\n", 2), 1);
	if (!start_simulation(data))
		return (destroy_data(data),
			ft_putstr_fd("Error ! Simulation failed.\n", 2), 1);
	destroy_data(data);
	return (0);
}
