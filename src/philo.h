/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:26:03 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/05/14 19:39:41 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define PHILO_I  1
#define DIE_I 2
#define EAT_I 3
#define SLEEP_I 4
#define MUST_EAT_I 5
#define MAX_PHILO_NUM 200

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t1;
	int				id;
	int				eat_num;
	int				status;
	int				eating;
	uint64_t		time_die;
	uint64_t		time_eat;
	uint64_t		time_sleep;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;
typedef struct s_data
{
	pthread_t		*tid;
	int				philo_num;
	int				meals_n;
	int				is_dead;
	int				finished;
	t_philo			*philos;
	uint64_t		time_die;
	uint64_t		time_eat;
	uint64_t		time_sleep;
	u_int64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_data;
int	ft_atoi(const char *str);
void init(t_data *data, char **argv, int argc);

#endif