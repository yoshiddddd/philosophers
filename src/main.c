/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:25:40 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/05/28 13:49:00 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_philo_num(char *args)
{
    if(ft_atoi(args)>MAX_PHILO_NUM || ft_atoi(args)<0)
        return 1;
    return 0;
}
int error_msg(char *message)
{
        printf("Invalid %s\n",message);
        return 1;
}

int check_arg_content(char *args)
{
    int i;
    i = 0;
    
    if(ft_atoi(args)<=0)
        return 1;
    while(args[i]!='\0')
    {
        if(args[i]<'0'||args[i]>'9')
            return 1;
        i++;
    }
    return 0;
}

int check_args(char **argv, int argc)
{
    if(check_philo_num(argv[PHILO_I]) == 1)
        return error_msg("philosophers number");
    if(check_arg_content(argv[DIE_I]) == 1)
        return error_msg("time to die");
    if(check_arg_content(argv[EAT_I]) == 1)
        return error_msg("time to eat");
    if(check_arg_content(argv[SLEEP_I]) == 1)
        return error_msg("time to sleep");
    if(argc == 6 && check_arg_content(argv[MUST_EAT_I]) == 1)
        return error_msg("must eat num");

    return 0;
}


int main(int argc , char **argv)
{
    t_data data;
    // char err_msg;
    if(argc!=5 && argc!=6)
        return  error_msg("args");
    if(check_args(argv,argc) == 1)
        return 1;
    init(&data,argv,argc);
    start_threads(&data);
    // printf("philo_num: %d\n",data.time_die);
    destroy_mutex("destroy mutex", &data);
    // pthread_create
}
