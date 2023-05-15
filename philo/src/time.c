/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:15:36 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/11 15:21:20 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

u_int64_t	timestamp(u_int64_t start)
{
	return (get_time() - start);
}

void	for_wait(u_int64_t time, t_philo *philo)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		if (exit_check(philo) == true)
			return ;
		usleep(100);
	}
}
