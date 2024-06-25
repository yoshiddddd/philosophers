/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:25:40 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/06/18 15:13:20 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"




int main(int argc , char **argv)
{
    t_data data;
    t_philo philos[MAX_PHILO_NUM];
    pthread_mutex_t	forks[MAX_PHILO_NUM];
    // char err_msg;
    if(argc!=5 && argc!=6)
        return  error_msg("args");
    if(check_args(argv,argc) == 1)
        return 1;
    init_data_forks(&data,philos,forks,ft_atoi(argv[PHILO_I]));
    init_philos(&data,philos, forks, argv);
    start_threads(&data, forks);
    destroy_mutex(NULL, &data,forks);
    return 1;
    // pthread_create
}
