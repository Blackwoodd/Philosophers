/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:41:23 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/15 13:56:12 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	create_philo(t_philo *philo)
{
	pthread_t	*id;
	pthread_t	kill;
	pthread_t	eat;
	int			i;

	i = -1;
	eat = 0;
	id = malloc(sizeof(pthread_t) * (philo->data->number_of_philosophers));
	if (id == NULL)
		return ;
	while (++i < philo->data->number_of_philosophers)
		pthread_create(&id[i], NULL, life_philosopher, (void *)&philo[i]);
	pthread_create(&kill, NULL, death, (void *)philo);
	if (philo->data->must_eat > 0)
	{	
		pthread_create(&eat, NULL, count_meal, (void *)philo);
		pthread_join(eat, NULL);
	}
	pthread_join(kill, NULL);
	i = -1;
	while (++i < philo->data->number_of_philosophers)
		pthread_join(id[i], NULL);
	destroy_mutex(philo);
	free(id);
}

int	main(int argc, char *argv[])
{
	t_philo			*philo;

	if (argc >= 5 && argc <= 6)
	{
		philo = init_struct(argc, argv);
		create_philo(philo);
		free_all(philo);
	}
	return (0);
}
