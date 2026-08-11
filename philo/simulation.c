/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: impinto <impinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 21:29:48 by impinto           #+#    #+#             */
/*   Updated: 2026/08/11 17:20:13 by impinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	take_forks(t_philo *philo)
{
	int	first;
	int	second;

	while (!check_stop(philo->data) && should_wait(philo))
		usleep(300);
	if (check_stop(philo->data))
		return (0);
	if (philo->id % 2 == 0)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(&philo->data->forks[first]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[second]);
	print_status(philo, "has taken a fork");
	return (1);
}

static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mtx);
	philo->last_meal_ms = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mtx);
	print_status(philo, "is eating");
	usleep(philo->data->t_eat * 1000);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->n_philo == 1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_status(philo, "has taken a fork");
		while (!check_stop(philo->data))
			usleep(philo->data->t_die * 1000);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return (NULL);
	}
	while (!check_stop(philo->data) && (philo->data->must_eat < 0
			|| philo->meals_eaten < philo->data->must_eat))
	{
		if (!take_forks(philo))
			break ;
		philo_eat(philo);
		release_forks(philo);
		print_status(philo, "is sleeping");
		usleep(1000);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	pthread_t	monitor;
	int			i;

	data->start_ms = get_time_ms();
	i = -1;
	while (++i < data->n_philo)
		data->philos[i].last_meal_ms = data->start_ms;
	i = -1;
	while (++i < data->n_philo)
		if (pthread_create(&data->philos[i].thread, NULL,
				routine, &data->philos[i]) != 0)
			return (0);
	if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
		return (0);
	i = -1;
	while (++i < data->n_philo)
		pthread_join(data->philos[i].thread, NULL);
	pthread_join(monitor, NULL);
	return (1);
}
