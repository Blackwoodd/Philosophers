/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:03:34 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/15 13:56:43 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_all(t_philo *philo)
{
	if (philo != NULL && philo->data != NULL && philo->data->mutex != NULL)
		free (philo->data->mutex);
	if (philo != NULL && philo->data != NULL)
		free (philo->data);
	if (philo != NULL && philo->forks != NULL)
		free (philo->forks);
	if (philo != NULL)
		free (philo);
}
