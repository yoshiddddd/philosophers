/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoshida <kyoshida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:25:40 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/06/29 16:05:05 by kyoshida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			philos[MAX_PHILO_NUM];
	pthread_mutex_t	forks[MAX_PHILO_NUM];

	if (argc != 5 && argc != 6)
		return (error_msg("args"));
	if (check_args(argv, argc) == 1)
		return (1);
	init_data_forks(&data, philos, forks, ft_atoi(argv[PHILO_I]));
	init_philos(&data, philos, forks, argv);
	start_threads(&data, forks);
	destroy_mutex(NULL, &data, forks);
	return (0);
}
