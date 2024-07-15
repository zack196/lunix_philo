/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:54:44 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/07/14 07:31:43 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosophers(t_table_philo *table)
{
	int	i;

	i = -1;
	if (pthread_create(&table->monit, NULL
				, monitoring_philo, (void *)table))
		return (printf("error creating thread\n"));
	while (++i < table->nbr_philo)
		if (pthread_create(&table->all_philos[i].philo_thread, NULL
				, philo_routine, (void *)&table->all_philos[i]))
			return (printf("error creating thread\n"));
	set_long(table->table_lock, &table->start_time, now());
	set_bool(table->table_lock, &table->begin_simulation, true);
	i = -1;
	while (++i < table->nbr_philo)
		if (pthread_join(table->all_philos[i].philo_thread, NULL))
			return (printf("error joining thread\n"));
	if (pthread_join(table->monit, NULL))
		return (printf("error join thread\n"));
	pthread_mutex_unlock(&table->record);
	return (0);
}

void	clean_up(t_table_philo *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_philo)
	{
		pthread_mutex_destroy(&table->all_fork[i]);
		pthread_mutex_destroy(&table->all_philos[i].philo_lock);
	}
	pthread_mutex_destroy(table->table_lock);
	pthread_mutex_destroy(&table->record);
	free(table->all_fork);
	free(table->all_philos);	
}

int	main(int ac, char **av)
{
	t_table_philo	table;

	if ((ac != 5 && ac != 6) || !init_table(&table, av))
		return (1);
	if (philosophers(&table))
		return (1);
	clean_up(&table);
	return (0);
}
