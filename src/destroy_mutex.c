/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:41:03 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/05/28 13:52:23 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void destroy_mutex(char *str,t_data *data)
{
    int i;

    printf("%s\n", str);
    i = 0;
    pthread_mutex_destroy(&data->lock);
    pthread_mutex_destroy(&data->write);
    while (i < data->philo_num)
    {
        pthread_mutex_destroy(&data->philos[i].lock);
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    free(data->forks);
}