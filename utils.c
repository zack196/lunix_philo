/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:55:08 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/07/14 07:43:34 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(char *str)
{
	unsigned long	nbr;
	int				i;
	int				sign;

	i = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			return (printf("nbr should be positive!\n"), 0);
	nbr = 0;
	while ('0' <= str[i] && str[i] <= '9')
		nbr = 10 * nbr + (str[i++] - '0');
	if (nbr > LONG_MAX || i > 19 || str[i] != 0)
		return (printf("error input!\n"), 0);// -42
	return (nbr);
}

long	now(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf("time function fealed!\n"));
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
#include <string.h>
void	record(t_philo *philo, char *str)
{
	t_table_philo	*all;
	long			start;

	all = philo->table;
	start = get_long(all->table_lock, &all->start_time);
	pthread_mutex_lock(&all->record);
	if (!get_bool(philo->table->table_lock, &philo->table->end_simulation))
		printf("%ld %ld %s\n", now() - start, philo->philo_id, str);
	if (!strncmp("died", str, 4))
		printf("%ld %ld died\n", now() - start, philo->philo_id);
	pthread_mutex_unlock(&all->record);
}

void	ft_sleep(long ms)
{
	long	time_now;

	time_now = now();
	while (now() - time_now < ms)
		usleep(100);
}
