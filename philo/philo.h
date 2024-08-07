/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:26:03 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/07/04 10:16:52 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# define PHILO_I 1
# define DIE_I 2
# define EAT_I 3
# define SLEEP_I 4
# define MUST_EAT_I 5
# define MAX_PHILO_NUM 1000

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t1;
	int				id;
	int				eat_num;
	int				eating;
	int				*is_dead;
	int				meals_n;
	size_t			last_eat;
	size_t			time_die;
	size_t			time_eat;
	size_t			start_time;
	size_t			time_sleep;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*write;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}					t_philo;
typedef struct s_data
{
	pthread_t		*tid;
	int				philo_num;
	int				count_eat;
	int				is_dead;
	int				finished;
	t_philo			*philos;
	uint64_t		time_die;
	uint64_t		time_eat;
	uint64_t		time_sleep;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write;
}					t_data;
int					ft_atoi(const char *str);
void				init_philos(t_data *data, t_philo *philos,
						pthread_mutex_t *forks, char **argv);
size_t				current_time(void);
void				init_data_forks(t_data *data, t_philo *philo,
						pthread_mutex_t *forks, int philo_num);
int					start_threads(t_data *data, pthread_mutex_t *forks);
void				sleep2think(t_philo *philo);
void				eat(t_philo *philo);
int					my_usleep(size_t milliseconds);
void				write_msg(char *str, t_philo *philo, int id);
void				*routine(void *p);
void				destroy_mutex(char *message, t_data *data,
						pthread_mutex_t *forks);
int					dead_judge(t_philo *philo);
void				*observer_routine(void *p);
int					check_args(char **argv, int argc);
int					error_msg(char *message);

#endif