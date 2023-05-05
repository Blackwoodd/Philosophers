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

bool	exit_check(t_philo *philo)
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
		if (philo->data->number_of_philosophers % 2 != 0)
			usleep(1000);
		else
			usleep(100);
		print_action(philo, THINK);
		for_wait(philo->data->time_to_think);
	}
	return (0);
}

bool	someone_starved(t_philo *philo, u_int64_t time_to_die)
{
	return ((get_time() - philo->last_meal) >= time_to_die);
}

void	kill_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex[EXIT]);
	philo->data->should_exit = true;
	pthread_mutex_unlock(&philo->data->mutex[EXIT]);
}

void	*death(void *arg)
{
	int		i;
	t_philo	*philo;

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

void	creat_philo(t_philo *philo)
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
		creat_philo(philo);
	}
	return (0);
}
