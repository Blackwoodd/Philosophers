/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:22:34 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/15 14:59:30 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_arg(int argc, t_data *data)
{
	if (data->number_of_philosophers <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| data->time_to_die > 3000 || data->time_to_eat > 1000
		|| data->time_to_sleep > 1000)
		return (1);
	if (argc == 6)
		if (data->must_eat <= 0)
			return (1);
	return (0);
}

static t_mutex	*init_mutex(void)
{
	int		i;
	t_mutex	*mutexes;

	i = 0;
	mutexes = NULL;
	mutexes = malloc(sizeof(t_mutex) * M_NUM);
	if (!mutexes)
		exit (0);
	while (i < M_NUM)
		pthread_mutex_init(&mutexes[i++], NULL);
	return (mutexes);
}

static t_data	*init_arg(int argc, char *argv[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit (0);
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = 0;
	if (check_arg(argc, data) == 1)
		exit (0);
	data->time_to_think = (data->time_to_eat - data->time_to_sleep + 1);
	data->should_exit = false;
	data->time = get_time();
	data->mutex = init_mutex();
	return (data);
}

int	init_philo(t_philo *philo, t_data *data)
{
	int		i;
	t_mutex	*fork;

	i = 0;
	fork = malloc(sizeof(t_mutex) * data->number_of_philosophers);
	if (!fork)
		return (FALSE);
	while (i < data->number_of_philosophers)
		pthread_mutex_init(&fork[i++], NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].forks = fork;
		philo[i].eat_times = 0;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1);
		if (i == (data->number_of_philosophers) - 1)
			philo[i].right_fork = 0;
		philo[i++].last_meal = get_time();
	}
	return (TRUE);
}

t_philo	*init_struct(int argc, char *argv[])
{
	t_philo		*philo;
	t_data		*data;

	data = init_arg(argc, argv);
	philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!philo)
		exit (0);
	philo->data = data;
	init_philo(philo, philo->data);
	return (philo);
}
