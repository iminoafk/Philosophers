/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: impinto <impinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 16:53:53 by impinto           #+#    #+#             */
/*   Updated: 2026/08/11 16:54:09 by impinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					n_philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					must_eat;
	long				start_ms;
	int					stop;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mtx;
	pthread_mutex_t		stop_mtx;
	pthread_mutex_t		meal_mtx;
	t_philo				*philos;
}						t_data;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	int					left_fork;
	int					right_fork;
	long				last_meal_ms;
	int					meals_eaten;
	t_data				*data;
}						t_philo;

int						ft_atoi(const char *s);
t_data					*fill_data_struct(int ac, char **av);
int						init_forks_data(t_data *data);
int						init_global_mutex(t_data *data);
int						init_philo(t_data *data);
void					destroy_global_mutex(t_data *data);
void					destroy_forks(t_data *data);
void					destroy_data(t_data *data);
long					get_time_ms(void);
int						check_stop(t_data *data);
void					set_stop(t_data *data);
void					print_status(t_philo *philo, char *msg);
int						should_wait(t_philo *philo);
void					*routine(void *arg);
void					*monitor_routine(void *arg);
int						start_simulation(t_data *data);

#endif