/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:25:49 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/06/15 11:15:22 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void init_data_forks(t_data *data, t_philo *philo,pthread_mutex_t *forks, int philo_num)
{
    int	i;
    data->is_dead = 0;
    data->philos = philo;
    pthread_mutex_init(&data->dead_lock, NULL);
    pthread_mutex_init(&data->write, NULL);
    pthread_mutex_init(&data->meal_lock, NULL);

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void init_args(t_philo *philo, char **argv)
{
    philo->time_die = ft_atoi(argv[DIE_I]);
    philo->time_eat = ft_atoi(argv[EAT_I]);
    philo->time_sleep = ft_atoi(argv[SLEEP_I]);
    philo->meals_n = -1;
    if (argv[MUST_EAT_I])
        philo->meals_n = ft_atoi(argv[MUST_EAT_I]);
}

void init_philos(t_data *data,t_philo *philos, pthread_mutex_t *forks,
		char **argv)
{
    int i;

    i = 0;
    while (i < ft_atoi(argv[PHILO_I]))
    {
        init_args(&philos[i],argv);
        philos[i].id = i + 1;
        philos[i].eat_num = 0;
        philos[i].status = 0;
        philos[i].eating = 0;
        philos[i].last_eat = get_current_time();
        philos[i].start_time = get_current_time();
        philos[i].write = &data->write;
        philos[i].dead_lock = &data->dead_lock;
        philos[i].meal_lock = &data->meal_lock;
        philos[i].data = data;
        philos[i].r_fork = &data->forks[i];
        philos[i].l_fork = &data->forks[(i + 1) % data->philo_num];
        
        i++;
    }

}

