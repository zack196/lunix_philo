/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:54:44 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/07/12 10:51:05 by zel-oirg         ###   ########.fr       */
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
	// monitoring_philo((void *)table);
	if (pthread_join(table->monit, NULL))
		return (printf("error join thread\n"));
	while (++i < table->nbr_philo)
		if (pthread_join(table->all_philos[i].philo_thread, NULL))
			return (printf("error joining thread\n"));
	return (0);
}

int	main(int ac, char **av)
{
	t_table_philo	table;

	if ((ac != 5 && ac != 6) || !init_table(&table, av))
		return (1);
	if (philosophers(&table))
		return (1);
	return (0);
}
