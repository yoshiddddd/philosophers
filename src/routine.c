/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:30:55 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/06/16 17:05:53 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void	think(t_philo *philo)
{
	print_message("is thinking", philo, philo->id);
}

void sleeping(t_philo *philo)
{
    print_message("is sleeping", philo, philo->id);
    ft_usleep(philo->time_sleep);
    // print_message("is thinking", philo, philo->id);
}

void eat(t_philo *philo)
{
    pthread_mutex_lock(philo->r_fork);
    print_message("has taken a fork", philo, philo->id);
    if(philo->data->philo_num == 1)
    {
        ft_usleep(philo->time_die);
        pthread_mutex_unlock(philo->r_fork);
        return ;
    }
    pthread_mutex_lock(philo->l_fork);
    print_message("has taken a fork", philo, philo->id);
    philo->eating = 1;
    print_message("is eating", philo, philo->id);
    pthread_mutex_lock(philo->meal_lock);
    philo->last_eat = get_current_time();
    philo->eat_num++;
    pthread_mutex_unlock(philo->meal_lock);
    ft_usleep(philo->time_eat);
    philo->eating = 0;
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}