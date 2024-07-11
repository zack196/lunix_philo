#ifndef PHILO_H
#define PHILO_H

# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_philo t_philo;
typedef struct s_table_philo t_table_philo;

struct s_philo
{
    long			philo_id;
    pthread_mutex_t	*l_fork;
    pthread_mutex_t	*r_fork;
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
	long			start_time;
	bool			begin_simulation;
	t_philo			*all_philos;
	pthread_mutex_t	*all_fork;
	pthread_mutex_t	record;
	pthread_mutex_t	table_lock;
};


/* Utils */
long    ft_atol(char *str);
long	now();
/* Routine */
void	*philo_routine(void *arg);


bool	get_bool(pthread_mutex_t *lock, bool value);
#endif