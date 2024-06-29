/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshida <kyoshida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:14:57 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/06/25 17:49:07 by kyoshida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_threads(t_data *data, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &observer_routine, data->philos) != 0)
		destroy_mutex("Thread creation error", data, forks);
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_create(&data->philos[i].t1, NULL, &routine,
				&data->philos[i]) != 0)
			destroy_mutex("Thread creation error", data, forks);
		i++;
	}
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		destroy_mutex("Thread join error", data, forks);
	while (i < data->philo_num)
	{
		if (pthread_join(data->philos[i].t1, NULL) != 0)
			destroy_mutex("Thread join error", data, forks);
		i++;
	}
	return (0);
}
