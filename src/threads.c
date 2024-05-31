/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:14:57 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/05/30 15:03:03 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

// int check_philo_status(t_philo *philo)
// {
//     uint64_t elapsed_time;
//    pthread_mutex_lock(&philo->lock);
//     elapsed_time = get_current_time() - philo->last_eat;
//     // printf("elapsed_time : %zu\n", philo->last_eat);
//     // printf("time_die : %llu\n", philo->data->time_die);
//         // printf("id : %d philo_eating %d\n", philo->id,philo->eating);
//     if(elapsed_time >= philo->data->time_die && philo->eating == 0)
//     {
//         philo->status = DIE_I;
//         pthread_mutex_unlock(&philo->lock);
//         return 1;
//     }
//     return 0;
// }
int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(&philo->lock);
	if (get_current_time() - philo->last_eat >= time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(&philo->lock), 1);
	pthread_mutex_unlock(&philo->lock);
	return (0);
}

int philo_is_dead(t_philo *philo)
{
    int i;

    i =0 ;
    while(i <philo->data->philo_num)
    {
        // check_philo_status(philos[i]);
        // ifphilos[i].status == DIE_I)
        // {
            if(philosopher_dead(&philo[i],philo[i].time_die)){
            pthread_mutex_lock(&philo[i].write);
            printf("%zu %d died\n", get_current_time(),philo[i].id);
            *philo->is_dead = 1;
            pthread_mutex_unlock(&philo[i].write);
            return 1;
        }
        i++;
    }
    return 0;
}
int check_all_ate(t_philo *philo)
{
    // int i;
    // i = 0;
        if(philo->data->meals_n == philo->data->count_eat)
        {
            pthread_mutex_lock(philo[0].dead_lock);
            philo->data->is_dead = 1;
            pthread_mutex_unlock(philo[0].dead_lock);
            return 1;
        }
        return 0;
}

void *observer_thread(void *arg)
{
    t_philo *philo;
    philo =(t_philo *)arg;
    while(1)
    {
        if(philo_is_dead(philo) == 1 || check_all_ate(philo) == 1){
            printf("hello\n");
            break;
        }
    }

    return arg;
}
int is_philo_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->is_dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
void *routine(void *pointer)
{
    t_philo *philo;

    philo = (t_philo *)pointer;
    if(philo->id % 2 == 0)
        ft_usleep(1);
    while(!is_philo_dead(philo))
    {
            eat(philo);
            sleep_now(philo);
            think(philo);
    }
    return pointer;
}

int start_threads(t_data *data)
{
    pthread_t observer;
    int i;

    i = 0;
    if(pthread_create(&observer, NULL, &observer_thread, (void *)data->philos)!=0)
        destroy_mutex("observer thread creation", data);    
    while(i < data->philo_num)
    {
        // printf("philo %d\n", data->philos[i].id);
        printf("heloo\n");
        if(pthread_create(&data->philos[i].t1, NULL, &routine, (void *)&data->philos[i])!=0)
        {
            //destroy all mutexes
            destroy_mutex("thread creation", data);
        }
        i++;
    }
    i = 0;
    if(pthread_join(observer, NULL)!=0)
        destroy_mutex("observer thread", data);
    while(i < data->philo_num)
    {
        if(pthread_join(data->philos[i].t1, NULL)!=0)
        {
            destroy_mutex("thread join", data);
            return 1;
        }
        i++;
    }
        return 0;
}