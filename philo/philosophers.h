/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: impinto <impinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:13:48 by impinto           #+#    #+#             */
/*   Updated: 2026/02/21 17:17:45 by impinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	int	n_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int must_eat;  
	long start_ms;
	int stop;      
}		t_data;

int		ft_atoi(const char *s);
t_data	*fill_data_struct(int ac, char **av);

#endif