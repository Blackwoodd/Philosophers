/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:39:36 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/12 16:06:03 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*count_meal(void *data)
{
	int		i;
	int		last_eat;
	t_philo	*philo;

	philo = (t_philo *)data;
	usleep(60000);
	while (exit_check(philo) == false)
	{
		i = 0;
		last_eat = 0;
		while (i < philo->data->number_of_philosophers)
		{
			pthread_mutex_lock(&philo->data->mutex[READ]);
			if (philo[i].eat_times >= philo->data->must_eat)
				last_eat++;
			pthread_mutex_unlock(&philo->data->mutex[READ]);
			i++;
		}
		usleep(100);
		if (last_eat == philo->data->number_of_philosophers)
			return (kill_philo(philo), NULL);
	}
	return (EXIT_SUCCESS);
}

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
		return (EXIT_FAILURE);
	}
	choosing_fork(philo, 2);
	print_action(philo, FORK);
	print_action(philo, EAT);
	pthread_mutex_lock(&philo->data->mutex[READ]);
	if (philo->eat_times != -1)
		philo->eat_times++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->mutex[READ]);
	for_wait(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(&philo->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->forks[philo->right_fork]);
	return (EXIT_SUCCESS);
}

void	*life_philosopher(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	if ((philo->id % 2) == 0)
	{
		print_action(philo, THINK);
		usleep(60000);
	}
	while (exit_check(philo) == false)
	{
		ft_eating(philo);
		print_action(philo, SLEEP);
		for_wait(philo->data->time_to_sleep, philo);
		if (philo->data->number_of_philosophers % 2 == 1)
			usleep(1000);
		else
			usleep(100);
		print_action(philo, THINK);
		for_wait(philo->data->time_to_think, philo);
	}
	return (0);
}
