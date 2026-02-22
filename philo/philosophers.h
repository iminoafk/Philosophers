/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: impinto <impinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:13:48 by impinto           #+#    #+#             */
/*   Updated: 2026/02/22 21:57:09 by impinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	int id;
	pthread_t thread;
	int left_fork;
	int right_fork;
	long last_meal_ms;
	int meals_eaten;
	t_data *data;
}	t_philo;

typedef struct s_data
{
	int	n_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int must_eat;  
	long start_ms;
	int stop;
	pthread_mutex_t *forks;
	pthread_mutex_t print_mtx;
	pthread_mutex_t stop_mtx;
	pthread_mutex_t meal_mtx;
	t_philo *philos;
}		t_data;

int		ft_atoi(const char *s);
t_data	*fill_data_struct(int ac, char **av);

#endif