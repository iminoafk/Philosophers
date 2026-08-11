/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: impinto <impinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 00:00:00 by impinto           #+#    #+#             */
/*   Updated: 2026/08/11 00:00:00 by impinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_dead(t_philo *philo)
{
	long	elapsed;
	int		finished;

	pthread_mutex_lock(&philo->data->meal_mtx);
	elapsed = get_time_ms() - philo->last_meal_ms;
	finished = (philo->data->must_eat >= 0
			&& philo->meals_eaten >= philo->data->must_eat);
	pthread_mutex_unlock(&philo->data->meal_mtx);
	if (finished)
		return (0);
	return (elapsed > philo->data->t_die);
}

static int	all_ate_enough(t_data *data)
{
	int	i;
	int	done;

	i = 0;
	done = 1;
	while (i < data->n_philo)
	{
		pthread_mutex_lock(&data->meal_mtx);
		if (data->philos[i].meals_eaten < data->must_eat)
			done = 0;
		pthread_mutex_unlock(&data->meal_mtx);
		i++;
	}
	return (done);
}

static void	print_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mtx);
	pthread_mutex_lock(&philo->data->stop_mtx);
	philo->data->stop = 1;
	pthread_mutex_unlock(&philo->data->stop_mtx);
	printf("%ld %d died\n",
		get_time_ms() - philo->data->start_ms, philo->id);
	pthread_mutex_unlock(&philo->data->print_mtx);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!check_stop(data))
	{
		i = 0;
		while (i < data->n_philo)
		{
			if (is_dead(&data->philos[i]))
				return (print_death(&data->philos[i]), NULL);
			i++;
		}
		if (data->must_eat >= 0 && all_ate_enough(data))
			return (set_stop(data), NULL);
		usleep(1000);
	}
	return (NULL);
}
