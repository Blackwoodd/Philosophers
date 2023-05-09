/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:41:23 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/09 16:22:40 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	exit_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex[EXIT]);
	if (philo->data->should_exit == true)
		return (pthread_mutex_unlock(&philo->data->mutex[EXIT]), true);
	return (pthread_mutex_unlock(&philo->data->mutex[EXIT]), false);
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
		for_wait(philo->data->time_to_sleep);
		if (philo->data->number_of_philosophers % 2 == 1)
			usleep(1000);
		else
			usleep(100);
		print_action(philo, THINK);
		for_wait(philo->data->time_to_think);
	}
	return (0);
}

void	create_philo(t_philo *philo)
{
	pthread_t	*id;
	pthread_t	kill;
	int			i;

	i = -1;
	id = malloc(sizeof(pthread_t) * (philo->data->number_of_philosophers));
	if (id == NULL)
		return ;
	while (++i < philo->data->number_of_philosophers)
		pthread_create(&id[i], NULL, life_philosopher, (void *)&philo[i]);
	pthread_create(&kill, NULL, death, (void *)philo);
	i = -1;
	while (++i < philo->data->number_of_philosophers)
		pthread_join(id[i], NULL);
	destroy_mutex(philo);
	free(id);
}

int	main(int argc, char *argv[])
{
	t_philo			*philo;

	if (argc > 1)
	{
		philo = init_struct(argv);
		create_philo(philo);
	}
	return (0);
}
