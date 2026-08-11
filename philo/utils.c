/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: impinto <impinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 00:00:00 by impinto           #+#    #+#             */
/*   Updated: 2026/08/10 00:00:00 by impinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	check_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->stop_mtx);
	stop = data->stop;
	pthread_mutex_unlock(&data->stop_mtx);
	return (stop);
}

void	set_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_mtx);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mtx);
}

void	print_status(t_philo *philo, char *msg)
{
	long	t;

	pthread_mutex_lock(&philo->data->print_mtx);
	if (!check_stop(philo->data))
	{
		t = get_time_ms() - philo->data->start_ms;
		printf("%ld %d %s\n", t, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_mtx);
}

int	should_wait(t_philo *philo)
{
	t_data	*data;
	t_philo	*left;
	t_philo	*right;
	int		wait;

	data = philo->data;
	left = &data->philos[(philo->left_fork - 1 + data->n_philo)
		% data->n_philo];
	right = &data->philos[philo->right_fork];
	pthread_mutex_lock(&data->meal_mtx);
	wait = 0;
	if ((data->must_eat < 0 || left->meals_eaten < data->must_eat)
		&& philo->last_meal_ms > left->last_meal_ms)
		wait = 1;
	if ((data->must_eat < 0 || right->meals_eaten < data->must_eat)
		&& philo->last_meal_ms > right->last_meal_ms)
		wait = 1;
	pthread_mutex_unlock(&data->meal_mtx);
	return (wait);
}
