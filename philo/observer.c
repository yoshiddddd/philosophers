/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshida <kyoshida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:56:50 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/06/25 17:53:35 by kyoshida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	judge_dead(t_philo *philo, size_t time_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (current_time() - philo->last_eat >= time_die && philo->eating == 0)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

static int	check_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->philo_num)
	{
		if (judge_dead(&philos[i], philos[i].time_die))
		{
			write_msg("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->is_dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_ate(t_philo *philos)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	if (philos[0].meals_n == -1)
		return (0);
	while (i < philos[0].data->philo_num)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].eat_num >= philos[i].meals_n)
			finished++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (finished == philos[0].data->philo_num)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->is_dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*observer_routine(void *p)
{
	t_philo	*philos;

	philos = (t_philo *)p;
	while (1)
	{
		if (check_dead(philos) == 1 || check_ate(philos) == 1)
			break ;
	}
	return (p);
}
