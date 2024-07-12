/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:55:26 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/07/12 10:42:01 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_philo			t_philo;
typedef struct s_table_philo	t_table_philo;

struct s_philo
{
	long			philo_id;
	long			start_threads;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	philo_lock;
	bool			philo_eat;
	bool			philo_full;
	long			last_meal;
	long			count_meal;
	pthread_t		philo_thread;
	t_table_philo	*table;
};

struct s_table_philo
{
	long			nbr_philo;
	long			t2d;
	long			t2e;
	long			t2s;
	long			max_nbr_meals;
	long			start_time;//
	long			nbr_ready_philo;
	bool			begin_simulation;
	bool			end_simulation;
	t_philo			*all_philos;
	pthread_t		monit;
	pthread_mutex_t	*all_fork;
	pthread_mutex_t	record;
	pthread_mutex_t	*table_lock;
};

/* Utils */
long	ft_atol(char *str);
long	now(void);
void	ft_sleep(long ms);
void	record(t_philo *philo, char *str);
/* Routine */
void	*philo_routine(void *arg);

/*monitoring*/
void	*monitoring_philo(void *arg);

/* get and set */
bool	get_bool(pthread_mutex_t *lock, bool *value);
void	set_bool(pthread_mutex_t *lock, bool *dest, bool value);
void	set_long(pthread_mutex_t *lock, long *dest, long value);
long	get_long(pthread_mutex_t *lock, long *value);
void	long_p_p(pthread_mutex_t *lock, long *val);

int	init_table(t_table_philo *table, char **av);

#endif