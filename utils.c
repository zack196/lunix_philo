#include "philo.h"

long    ft_atol(char *str)
{
	unsigned	long	nbr;
	int	i;

	i = -1;
	nbr = 0;
	while (str[++i])
		nbr = 10 * nbr + (str[i] - '0');
	if (nbr > LONG_MAX || i > 19)
		return (printf("arg should be a long\n"),
			exit(EXIT_FAILURE), -1);
	return (nbr);
}

long	now()
{
	struct	timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf("time function fealed!\n"));
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	exit_err(char *err_msg)
{
	printf("%s\n", err_msg);
	exit(EXIT_FAILURE);
}
void	philo_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->all->write_lock);
	printf("%ld %d %s\n", now() - philo->all->start_time, philo->philo_id, str);
	pthread_mutex_lock(&philo->all->write_lock);
}