/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:35:21 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/09 16:08:23 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	destroy_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->number_of_philosophers)
	{
		pthread_mutex_destroy(&philo->data->mutex[i]);
		i++;
	}
	return (TRUE);
}