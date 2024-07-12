/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:55:13 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/07/12 10:42:19 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


bool	philo_die(t_philo *philo)
{
	long	delta_t;

	delta_t = now() - get_long(&philo->philo_lock, &philo->last_meal);
	if (delta_t > philo->table->t2d
		&& get_bool(&philo->philo_lock, &philo->philo_eat))
		return (true);
	return (false);
}

bool	one_philo_die(t_table_philo *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_philo)
	{
		if (philo_die(&table->all_philos[i]))
		{
			record(&table->all_philos[i], "died");
			return (true);
		}
	}
	return (false);
}

bool	all_philo_full(t_table_philo *table)
{
	int	i;
	int	full;

	i = -1;
	full = 0;
	while (++i < table->nbr_philo)
	{
		if (get_bool(&table->all_philos[i].philo_lock, &table->all_philos[i].philo_full))
			full++;
	}
	if (full == table->nbr_philo)
	{
		set_bool(table->table_lock, &table->end_simulation, true);
		record(&table->all_philos[0], "are philo full");
		return (true);
	}
	return (false);
}



void	*monitoring_philo(void *arg)
{
	t_table_philo *table;
	
	table = (t_table_philo *)arg;
	while (get_long(table->table_lock, &table->nbr_philo) != table->nbr_ready_philo)
		;
	while (1)
		if (one_philo_die(table) || all_philo_full(table))
		{
			set_bool(table->table_lock, &table->end_simulation, true);
			break ;
		}
	return NULL;
}