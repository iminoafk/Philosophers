/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: impinto <impinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 16:55:25 by impinto           #+#    #+#             */
/*   Updated: 2026/08/11 16:55:25 by impinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_global_mutex(t_data *data)
{
	pthread_mutex_destroy(&data->print_mtx);
	pthread_mutex_destroy(&data->stop_mtx);
	pthread_mutex_destroy(&data->meal_mtx);
}

void	destroy_forks(t_data *data)
{
	int	i;

	if (!data->forks)
		return ;
	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	data->forks = NULL;
}

void	destroy_data(t_data *data)
{
	if (!data)
		return ;
	destroy_forks(data);
	if (data->philos)
		free(data->philos);
	destroy_global_mutex(data);
	free(data);
}
