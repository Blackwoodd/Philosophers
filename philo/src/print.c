/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:16:20 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/10 11:14:51 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_action(t_philo *philo, char *code)
{
	unsigned long	start;

	pthread_mutex_lock(&philo->data->mutex[EXIT]);
	start = timestamp(philo->data->time);
	if (philo->data->should_exit == false)
		printf ("%lu %i %s\n", start, philo->id, code);
	pthread_mutex_unlock(&philo->data->mutex[EXIT]);
}
