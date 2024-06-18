/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:55:47 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/06/18 13:02:04 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void destroy_mutex(char *message, t_data *data, pthread_mutex_t *forks)
{
    int i;
    i = 0;
    while(i<data->philo_num)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
    pthread_mutex_destroy(&data->dead_lock);
    pthread_mutex_destroy(&data->write);
    pthread_mutex_destroy(&data->meal_lock);
    if(message)
    printf("%s\n",message);
}


int dead_judge(t_philo *philo)
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

int	my_usleep(size_t milliseconds)
{
	size_t	start;

	start = current_time();
	while ((current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}