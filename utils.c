#include "philo.h"

long	ft_atol(char *str)
{
	unsigned long	nbr;
	int				i;
	int				sign;

	i = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
		{
			printf("nbr should be positive!\n");
			exit(1);
		}
	}
	nbr = 0;
	while (str[i])
		nbr = 10 * nbr + (str[i++] - '0');
	if (nbr > LONG_MAX || i > 19)
		return (printf("arg should be a long\n"),
			exit(EXIT_FAILURE), -1);
	return (nbr);
}

long	now(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf("time function fealed!\n"));
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	record(t_philo *philo, char *str)
{
	t_table_philo	*all;

	all = philo->table;
	pthread_mutex_lock(&all->record);
	printf("%ld %ld %s\n", now() - all->start_time, philo->philo_id, str);
	pthread_mutex_unlock(&all->record);
}

void	ft_sleep(long ms)
{
	long	us;

	us = ms * 1000;
	if (usleep(us) == -1)
		exit(EXIT_FAILURE);
}
