#include "philo.h"
// void	set_long(pthread_mutex_t *lock, &)

long	get_long(pthread_mutex_t *lock, long value)
{
	long	ret;
	pthread_mutex_lock(lock);
	ret = value;
	pthread_mutex_unlock(lock);
	return (ret);
}

bool	get_bool(pthread_mutex_t *lock, bool value)
{
	bool	ret;
	pthread_mutex_lock(lock);
	ret = value;
	pthread_mutex_unlock(lock);
	return (ret);
}