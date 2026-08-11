/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: impinto <impinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 22:06:20 by impinto           #+#    #+#             */
/*   Updated: 2026/08/11 16:55:25 by impinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_data	*fill_data_struct(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->n_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->must_eat = -1;
	data->start_ms = 0;
	data->stop = 0;
	data->forks = NULL;
	data->philos = NULL;
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	if (!init_global_mutex(data))
		return (free(data), NULL);
	if (!init_forks_data(data))
		return (destroy_global_mutex(data), free(data), NULL);
	if (!init_philo(data))
		return (destroy_data(data), NULL);
	return (data);
}

int	init_global_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->meal_mtx, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->stop_mtx, NULL) != 0)
	{
		pthread_mutex_destroy(&data->meal_mtx);
		return (0);
	}
	if (pthread_mutex_init(&data->print_mtx, NULL) != 0)
	{
		pthread_mutex_destroy(&data->stop_mtx);
		pthread_mutex_destroy(&data->meal_mtx);
		return (0);
	}
	return (1);
}

int	init_forks_data(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&data->forks[i]);
			}
			free(data->forks);
			data->forks = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_philo(t_data *data)
{
	int		i;
	t_philo	*philo;

	data->philos = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philos)
		return (0);
	philo = data->philos;
	i = 0;
	while (i < data->n_philo)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->meals_eaten = 0;
		philo->data = data;
		philo->right_fork = (i + 1) % data->n_philo;
		philo->left_fork = i;
		i++;
	}
	return (1);
}
