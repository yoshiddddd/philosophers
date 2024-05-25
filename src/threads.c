/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:14:57 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/05/25 00:09:10 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_philo_status(t_philo *philo)
{
    int elapsed_time;
    pthreads_mutex_lock(&philo->lock);
    elapsed_time = get_current_time() - philo->last_eat;
    if(elapsed_time > philo->data->time_die)
    {
        philo->status = DIE_I;
        pthread_mutex_unlock(&philo->lock);
        return 1;
    }
}


int philo_is_dead(t_data *data)
{
    int i;

    i =0 ;
    while(i < data->philo_num)
    {
        check_philo_status(&data->philos[i]);
        if(data->philos[i].status == DIE_I)
        {
            pthread_mutex_lock(&data->write);
            printf("%llu %d died\n", get_time() - data->start_time, data->philos[i].id);
            data->is_dead = 1;
            pthread_mutex_unlock(&data->write);
            return 1;
        }
        i++;
    }
    return 0;
}

void observer_thread(void *arg)
{
    t_data *data;
    data =(t_data *)arg;
    while(1)
    {
        if(philo_is_dead(data) == 1 )
            break;
    }
}
int is_philo_dead(t_philo *philo)
{
    int status;

    pthread_mutex_lock(&philo->data->lock);
    if(philo->data->is_dead == 1)
        status = 1;
    else
        status = 0;
    pthread_mutex_unlock(&philo->data->lock);
    return status;
}
void routine(void *pointer)
{
    t_philo *philo;

    philo = (t_philo *)pointer;
    if(philo->id % 2 == 0)
        usleep(100);
    while(is_philo_dead(philo) == 0)
    {
            eat(philo);
            sleep(philo);
            think(philo);
    }
}

int start_threads(t_data *data)
{
    pthread_t observer;
    int i;

    i = 0;
    if(pthread_create(&observer, NULL, observer_thread, (void *)data)!=0)
    //destroy all mutexes
    while(i < data->philo_num)
    {
        if(pthread_create(&data->philos[i].t1, NULL, routine, (void *)&data->philos[i])!=0)
        {
            //destroy all mutexes
            return 1;
        }
        i++;
    }
    i = 0;
    if(pthread_join(observer, NULL)!=0)
        //destroy all mutexes
    while(i < data->philo_num)
    {
        if(pthread_join(data->philos[i].t1, NULL)!=0)
        {
            //destroy all mutexes
            return 1;
        }
        i++;
    }
        return 1;
}