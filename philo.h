#ifndef PHILO_H
#define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <time.h>
# include <limits.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_philo t_philo;
typedef struct s_all_philo t_all_philo;

typedef	struct s_fork
{
	pthread_mutex_t	fork;
	int				id_fork;
}	t_fork;


struct s_all_philo 
{
	int				nbr_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				max_meal;

	long			start_time;
	bool			begin_meal;
	bool			end_meal;

    pthread_mutex_t	lock;
    pthread_mutex_t	write_lock;
	t_philo			*all_philo;
	t_fork			*all_fork;
};

struct s_philo
{
	pthread_t		philo_thread;
	int				philo_id;
	t_fork			l_fork;
	t_fork			r_fork;

	t_all_philo		*all;
	long			last_meal_time;
};



/*Parcing of the programe*/
int chec_arg(char **av);

/*Utils*/
long    ft_atol(char *str);
long	now(void);
void	exit_err(char *err_msg);
void	philo_print(t_philo *philo, char *str);
/*initialisation*/
void	init_all(t_all_philo *all, char **av);
void	threads(t_all_philo *all);
/*Routine*/
void	*philo_routine(void *arg);
/* Set and Get */
void	set_long(pthread_mutex_t *lock, long *dest, long value);
void	set_bool(pthread_mutex_t *lock, bool *dest, bool value);
long    get_long(pthread_mutex_t *lock, long value);
bool    get_bool(pthread_mutex_t *lock, bool value);
#endif