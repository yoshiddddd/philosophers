/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:14:57 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/05/15 16:25:59 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void observer_thread(void *arg)
{
    t_data *data;
    data =(t_data *)arg;
    
}


int start_threads(t_data *data)
{
    pthread_t observer;
    
    if(pthread_create(&observer, NULL, observer_thread, (void *)data)!=0)
        return 1;
}