/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:41:23 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/04 17:59:44 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int     someone_starved(t_philo *philo, u_int64_t time_to_die)
{
        return ((get_time() - philo->last_meal) >= time_to_die);
}

void    kill_philo(t_philo *philo)
{
        pthread_mutex_lock(&philo->data->mutex[EXIT]);
        philo->data->should_exit = true;
        pthread_mutex_unlock(&philo->data->mutex[EXIT]);
}

void    *death(void *arg)
{
        int             i;
        t_philo *philo;

        philo = (t_philo *)arg;
        usleep(60000);
        while (exit_check(philo) == false)
        {
                i = 0;
                while (i < philo->data->number_of_philosophers)
                {
                        pthread_mutex_lock(&philo->data->mutex[READ]);
                        if (someone_starved(&philo[i], philo[i].data->time_to_die))
                        {
                                printf("%i starved\n", philo->id);
                                exit(1);
                                pthread_mutex_unlock(&philo->data->mutex[READ]);
                                kill_philo(philo);
                                return (death(&philo[i]), NULL);
                        }
                        pthread_mutex_unlock(&philo->data->mutex[READ]);
                        i++;
                }
                usleep(100);
        }
        return (EXIT_SUCCESS);
}
