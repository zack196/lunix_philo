/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:54:52 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/07/12 11:11:41 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	record(philo, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	record(philo, "has taken a fork");
	
	set_bool(&philo->philo_lock, &philo->philo_eat, true);
	set_long(&philo->philo_lock, &philo->last_meal, now());
	record(philo, "is eating");
	ft_sleep(philo->table->t2d);
	philo->count_meal++;
	set_bool(&philo->philo_lock, &philo->philo_eat, false);

	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleep_think(t_philo *philo)
{
	record(philo, "is sleeping");
	ft_sleep(philo->table->t2s);
	record(philo, "is thinking");
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!get_bool(philo->table->table_lock, &philo->table->begin_simulation))
		;
	long_p_p(philo->table->table_lock, &philo->table->nbr_philo);
	set_long(&philo->philo_lock, &philo->last_meal, now());
	if (philo->philo_id % 2 == 0)
		ft_sleep(philo->table->t2e * 0.8);
	while (!get_bool(philo->table->table_lock, &philo->table->end_simulation))
	{
		if (philo->count_meal == philo->table->max_nbr_meals)
		{
			set_bool(&philo->philo_lock, &philo->philo_full, true);
			return (NULL);
		}
		eat(philo);
		sleep_think(philo);
	}
	return (NULL);
}
