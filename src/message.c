/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshida <kyoshida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:01:34 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/06/25 17:51:26 by kyoshida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(char *message)
{
	printf("Invalid %s\n", message);
	return (1);
}

void	write_msg(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write);
	time = current_time() - philo->start_time;
	if (!dead_judge(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write);
}
