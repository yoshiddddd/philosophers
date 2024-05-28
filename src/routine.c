/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:30:55 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/05/28 13:19:37 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void think(t_philo *philo)
{
    if(philo)
    ;
    printf("is thinking\n");//ここにタイムスタンプなどを入れる
}

void sleep_now(t_philo *philo)
{
    printf("is sleeping\n");//ここにタイムスタンプなどを入れる
    size_t start_time;
    start_time = get_current_time();
    while((get_current_time() - start_time) < philo->time_sleep)
    {
        usleep(400);
    }
}

void eat(t_philo *philo)
{
    pthread_mutex_lock(philo->r_fork);
    printf("has taken a fork\n");//ここにタイムスタンプなどを入れる
    pthread_mutex_lock(philo->l_fork);
    printf("has taken a fork\n");//ここにタイムスタンプなどを入れる
    philo->eating = 1;
    // printf()
    pthread_mutex_lock(philo->lock);
    philo->last_eat = get_current_time();
    philo->eat_num+=1;
    philo->data->count_eat += 1;
    pthread_mutex_unlock(philo->lock);
    philo->eating = 0;
    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);
}