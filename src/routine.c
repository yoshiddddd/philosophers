/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:30:55 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/06/18 12:58:52 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void sleep2think(t_philo *philo)
{
    write_msg("is sleeping", philo, philo->id);
    my_usleep(philo->time_sleep);
    write_msg("is thinking", philo, philo->id);
}

void eat(t_philo *philo)
{
    pthread_mutex_lock(philo->r_fork);
    write_msg("has taken a fork", philo, philo->id);
    if(philo->data->philo_num == 1)
    {
        my_usleep(philo->time_die);
        pthread_mutex_unlock(philo->r_fork);
        return ;
    }
    pthread_mutex_lock(philo->l_fork);
    write_msg("has taken a fork", philo, philo->id);
    philo->eating = 1;
    write_msg("is eating", philo, philo->id);
    pthread_mutex_lock(philo->meal_lock);
    philo->last_eat = current_time();
    philo->eat_num++;
    pthread_mutex_unlock(philo->meal_lock);
    my_usleep(philo->time_eat);
    philo->eating = 0;
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}
void *routine(void *p)
{
    t_philo *philo;
    
    philo = (t_philo *)p;
    if(philo->id%2==0)
        my_usleep(1);
    while(!dead_judge(philo))
    {
        eat(philo);
        sleep2think(philo);
    }
    return p;
}