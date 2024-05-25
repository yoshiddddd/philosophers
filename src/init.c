/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:25:49 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/05/16 19:06:14 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_data(t_data *data, char **argv, int argc)
{
    data->time_die = ft_atoi(argv[DIE_I]);
    data->time_eat = ft_atoi(argv[EAT_I]);
    data->time_sleep = ft_atoi(argv[SLEEP_I]);
    data->philo_num = ft_atoi(argv[PHILO_I]);
    if (argc == 6)
    data->meals_n = ft_atoi(argv[MUST_EAT_I]);
    else
    data->meals_n = -1;
}

void init_locks_and_forks(t_data *data)
{
    int i;

    i = 0;
    pthread_mutex_init(&data->lock, NULL);
    pthread_mutex_init(&data->write, NULL);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
    while (i < data->philo_num)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
}

void init_philos(t_data *data)
{
    int i;

    i = 0;
    data->philos = malloc(sizeof(t_philo) * data->philo_num);
    while (i < data->philo_num)
    {
        data->philos[i].id = i + 1;
        data->philos[i].eat_num = 0;
        data->philos[i].status = 0;
        data->philos[i].eating = 0;
        data->philos[i].last_eat = get_current_time();
        data->philos[i].time_die = data->start_time + data->time_die;
        data->philos[i].time_eat = data->time_eat;
        data->philos[i].time_sleep = data->time_sleep;
        data->philos[i].data = data;
        data->philos[i].r_fork = &data->forks[i];
        data->philos[i].l_fork = &data->forks[(i + 1) % data->philo_num];
        pthread_mutex_init(&data->philos[i].lock, NULL);
        i++;
    }

}

void init(t_data *data, char **argv, int argc)
{
    init_data(data, argv, argc);
    init_locks_and_forks(data);
    init_philos(data);
}