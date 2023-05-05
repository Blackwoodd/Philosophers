/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:35:21 by nbechon           #+#    #+#             */
/*   Updated: 2023/04/27 15:52:26 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// static t_mutex	*init_mutex(void)
// {
// 	int		i;
// 	t_mutex	*mutexes;

// 	i = 0;
// 	mutexes = NULL;
// 	mutexes = malloc(sizeof(t_mutex) * M_NUM);
// 	while (i < M_NUM)
// 		pthread_mutex_init(&mutexes[i++], NULL);
// 	return (mutexes);
// }

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