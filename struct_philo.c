/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:56:06 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/07/12 10:31:53 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_init(t_table_philo *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_philo)
	{
		table->all_philos[i].philo_id = i + 1;
		table->all_philos[i].count_meal = 0;
		table->all_philos[i].table = table;
		table->all_philos[i].philo_eat = false;
		table->all_philos[i].philo_full = false;
		// table->all_philos[i].philo_ready = false;
		pthread_mutex_init(&table->all_philos[i].philo_lock, NULL);
		table->all_philos[i].r_fork = &table->all_fork[i];
		table->all_philos[i].l_fork
			= &table->all_fork[(i + 1) % table->nbr_philo];
	}
}

int	init_mutex(t_table_philo *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_philo)
	{
		if (pthread_mutex_init(&table->all_fork[i], NULL))
			return (printf("error init mutex!\n"), 1);
	}
	if (pthread_mutex_init(table->table_lock, NULL)
		&& pthread_mutex_init(&table->record, NULL))
		return (printf("error init mutex!\n"), 1);
	return (0);
}

int	init_table(t_table_philo *table, char **av)
{
	table->nbr_philo = ft_atol(av[1]);
	table->t2d = ft_atol(av[2]);
	table->t2e = ft_atol(av[3]);
	table->t2s = ft_atol(av[4]);
	table->begin_simulation = false;
	table->end_simulation = false;
	table->nbr_ready_philo = 0;
	if (av[5])
		table->max_nbr_meals = ft_atol(av[5]);
	else
		table->max_nbr_meals = -1;
	table->all_fork = malloc(sizeof (pthread_mutex_t) * table->nbr_philo);
	if (!table->all_fork)
		return (0);
	table->all_philos = malloc(sizeof (t_philo) * table->nbr_philo);
	if (!table->all_philos)
		return (0);
	philo_init(table);
	if (init_mutex(table))
		return (0);
	return (table->nbr_philo && table->t2d && table->t2e && table->t2s);
}
