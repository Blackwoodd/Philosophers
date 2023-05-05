/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:22:34 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/02 17:13:40 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static t_mutex	*init_mutex(void)
{
	int		i;
	t_mutex	*mutexes;

	i = 0;
	mutexes = NULL;
	mutexes = malloc(sizeof(t_mutex) * M_NUM);
	while (i < M_NUM)
		pthread_mutex_init(&mutexes[i++], NULL);
	return (mutexes);
}

static t_data	*init_arg(char *argv[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
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
	while (i < data->number_of_philosophers)
		pthread_mutex_init(&fork[i++], NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].forks = fork;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1);
		philo[i++].last_meal = get_time();
	}
	return (TRUE);
}

t_philo	*init_struct(char *argv[])
{
	t_philo	*philo;
	t_data	*data;

	data = init_arg(argv);
	philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	philo->data = data;
	init_philo(philo, philo->data);
	return (philo);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}
