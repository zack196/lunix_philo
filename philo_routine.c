#include "philo.h"

void    sleep_think(t_philo *philo)
{
    philo_print(philo, "is sleeping");
    // usleep(philo->all->time_to_sleep * 1000);
    philo_print(philo, "is thinking");
}

void    eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->r_fork.fork);
    philo_print(philo, "has taken a r_fork");// remove l_
    pthread_mutex_lock(&philo->l_fork.fork);
    philo_print(philo, "has taken a l_fork");//remove r_

    pthread_mutex_lock(&philo->l_fork.fork);
    pthread_mutex_lock(&philo->r_fork.fork);
}

void	*philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (!get_bool(&philo->all->lock, philo->all->begin_meal))
        ;
    if (philo->philo_id % 2 == 0)
        usleep((philo->all->time_to_eat / 2) * 1000);
    while (!get_bool(&philo->all->lock, philo->all->end_meal))
    {
        eat(philo);
        sleep_think(philo);
    }
    return (NULL);
}