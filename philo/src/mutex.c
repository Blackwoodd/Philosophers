/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:35:21 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/12 14:37:10 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroy_mutex(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data->number_of_philosophers)
		pthread_mutex_destroy(&philo->forks[i]);
	i = -1;
	while (++i < M_NUM)
		pthread_mutex_destroy(&philo->data->mutex[i]);
}
