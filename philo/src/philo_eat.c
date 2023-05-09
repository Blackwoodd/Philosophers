/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:39:36 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/09 15:23:57 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	choosing_fork(t_philo *philo, int order)
{
	if (order == 1)
	{
		if (philo->left_fork < philo->right_fork)
			pthread_mutex_lock(&philo->forks[philo->left_fork]);
		else
			pthread_mutex_lock(&philo->forks[philo->right_fork]);
	}
	else if (order == 2)
	{
		if (philo->left_fork < philo->right_fork)
			pthread_mutex_lock(&philo->forks[philo->right_fork]);
		else
			pthread_mutex_lock(&philo->forks[philo->left_fork]);
	}
}

int	ft_eating(t_philo *philo)
{
	choosing_fork(philo, 1);
	print_action(philo, FORK);
	if (philo->data->number_of_philosophers == 1)
	{
		pthread_mutex_unlock(&philo->forks[philo->right_fork]);
		return (EXIT_SUCCESS);
	}
	choosing_fork(philo, 2);
	print_action(philo, FORK);
	print_action(philo, EAT);
	pthread_mutex_lock(&philo->data->mutex[READ]);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->mutex[READ]);
	for_wait(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->forks[philo->right_fork]);
	return (EXIT_FAILURE);
}