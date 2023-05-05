/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:43:56 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/02 17:11:40 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>

# define FORK "has taken a fork"
# define THINK "is thinking"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define DIED "died"
# define TRUE 1
# define FALSE 0

typedef enum e_mutexes
{
	EXIT,
	READ,
	M_NUM
}				t_mutexes;

typedef pthread_mutex_t	t_mutex;

typedef struct s_data
{
	u_int64_t		time;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	time_to_think;
	int				number_of_philosophers;
	bool			should_exit;
	t_mutex			*mutex;
}				t_data;

typedef struct s_philo
{
	u_int64_t		last_meal;
	t_data			*data;
	t_mutex			*forks;
	int				right_fork;
	int				left_fork;
	int				id;
	int				eat_times;
}				t_philo;

int				ft_eating(t_philo *philo);

unsigned long	get_time(void);

int				ft_atoi(const char *str);

int				destroy_mutex(t_philo *philo);

void			create_philo(t_philo *philo);

int				init_philo(t_philo *philo, t_data *data);

t_philo			*init_struct(char *argv[]);

void			print_action(t_philo *philo, char *code);

u_int64_t		timestamp(u_int64_t start);

void			for_wait(u_int64_t time);

#endif