/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:26:03 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/04/03 20:29:31 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <limits.h>
#include <unistd.h>
#include <stdio.h>

#define PHILO_I  1
#define DIE_I 2
#define EAT_I 3
#define SLEEP_I 4
#define MUST_EAT_I 5
#define MAX_PHILO_NUM 200

int	ft_atoi(const char *str);

#endif