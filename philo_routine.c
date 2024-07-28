/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:54:52 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/07/28 08:38:24 by zel-oirg         ###   ########.fr       */
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
	record(philo, "is eating");
	set_long(&philo->philo_lock, &philo->last_meal, now());
	ft_sleep(philo->table->t2e);
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
void	routine_one_philo(t_philo *philo)
{
	while (!get_bool(philo->table->table_lock, &philo->table->end_simulation))
	{
		ft_sleep(100);
	}
}
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!get_bool(philo->table->table_lock, &philo->table->begin_simulation))
		;
	long_p_p(philo->table->table_lock, &philo->table->nbr_ready_philo);
	set_long(&philo->philo_lock, &philo->last_meal, now());
	if (philo->table->nbr_philo == 1)
		return (routine_one_philo(philo), NULL);
	if (philo->philo_id % 2 == 0)
		ft_sleep(philo->table->t2e * 0.8);
	while (!get_bool(philo->table->table_lock, &philo->table->end_simulation))
	{
		eat(philo);
		if (philo->count_meal >= philo->table->max_nbr_meals 
			&& philo->table->max_nbr_meals >= 0)
		{
			set_bool(&philo->philo_lock, &philo->philo_full, true);
			return (NULL);
		}
		sleep_think(philo);
	}
	return (NULL);//715 - 2
}
