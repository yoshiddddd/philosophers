/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:14:57 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/06/16 20:05:20 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int judge_dead(t_philo *philo, size_t time_die)
{
        pthread_mutex_lock(philo->meal_lock);
    if(get_current_time() - philo->last_eat >= time_die && philo->eating == 0)
    {
        pthread_mutex_unlock(philo->meal_lock);
        return 1;
    }
    pthread_mutex_unlock(philo->meal_lock);
    return 0;
}

int check_dead(t_philo *philos)
{
    int i;
    
    i = 0;
    while(i<philos->data->philo_num)
    {
        if(judge_dead(&philos[i],philos[i].time_die))
        {
            print_message("died", &philos[i], philos[i].id);
            pthread_mutex_lock(philos[0].dead_lock);
            *philos->is_dead = 1;
            pthread_mutex_unlock(philos[0].dead_lock);
            return 1;
        }
        i++;
    }
    return 0;

}


void *observer_routine(void *p)
{
    t_philo *philos;
    
    philos = (t_philo *)p;
    while(1)
    {
        if(check_dead(philos) == 1)
            break;
    }
    return p;
}
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

int dead_loop(t_philo *philo)
{
    // if(philo->dead_lock == NULL)
        // return (printf("hogehoge\n"),1);
    pthread_mutex_lock(philo->dead_lock);
    if(*philo->is_dead == 1)
    {
        return (pthread_mutex_unlock(philo->dead_lock), 1);
    }
    pthread_mutex_unlock(philo->dead_lock);
    return 0;
}
void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write);
	time = get_current_time() - philo->start_time;
	if (!dead_loop(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write);
}

void *routine(void *p)
{
    t_philo *philo;
    
    philo = (t_philo *)p;
    if(philo->id%2==0)
        ft_usleep(1);
    while(!dead_loop(philo))
    {
        eat(philo);
        sleeping(philo);
        think(philo);
    }
    return p;
}

int start_threads(t_data *data, pthread_mutex_t *forks)
{
    pthread_t observer;
    int i;

    if(pthread_create(&observer, NULL, &observer_routine, data->philos)!=0)
        destroy_mutex("Thread creation error", data, forks);
    i = 0;
    while(i<data->philo_num)
    {
        if(pthread_create(&data->philos[i].t1, NULL, &routine, &data->philos[i])!=0)
            destroy_mutex("Thread creation error", data, forks);
        i++;
    }
    i=0;
    if(pthread_join(observer, NULL)!=0)
        destroy_mutex("Thread join error", data, forks);
    while(i<data->philo_num)
    {
        if(pthread_join(data->philos[i].t1, NULL)!=0)
            destroy_mutex("Thread join error", data, forks);
        i++;
    }
    return 0;
}