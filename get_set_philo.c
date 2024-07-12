/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-oirg <zel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:55:20 by zel-oirg          #+#    #+#             */
/*   Updated: 2024/07/12 10:42:07 by zel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_bool(pthread_mutex_t *lock, bool *value)
{
	bool	ret_val;

	pthread_mutex_lock(lock);
	ret_val = *value;
	pthread_mutex_unlock(lock);
	return (ret_val);
}

long	get_long(pthread_mutex_t *lock, long *value)
{
	long	ret_val;

	pthread_mutex_lock(lock);
	ret_val = *value;
	pthread_mutex_unlock(lock);
	return (ret_val);
}

void	set_bool(pthread_mutex_t *lock, bool *dest, bool value)
{
	pthread_mutex_lock(lock);
	*dest = value;
	pthread_mutex_unlock(lock);
}

void	set_long(pthread_mutex_t *lock, long *dest, long value)
{
	pthread_mutex_lock(lock);
	*dest = value;
	pthread_mutex_unlock(lock);
}

void	long_p_p(pthread_mutex_t *lock, long *val)
{
	pthread_mutex_lock(lock);
	*val = *val + 1;
	pthread_mutex_unlock(lock);
}