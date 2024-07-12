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
