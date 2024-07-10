#include "philo.h"

int	chec_arg(char **av)
{
	int i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = 0;
		if (av[i][j] == '-'|| av[i][j] == '+')
			if (av[i][j++] == '-')
				return (0);
		while ('0' <= av[i][j] && av[i][j] <= '9' && av[i][j])
			j++;
		if (av[i][j])
			return (0);
	}
	return (1);
}

void	init_philo(t_all_philo *all)
{
	int	i;
	t_philo	*philos;

	i = -1;
	philos = all->all_philo;
	while (++i < all->nbr_philo)
	{
		philos[i].philo_id = i + 1;
		philos[i].all = all;
		philos[i].last_meal_time = now();
		philos[i].l_fork = all->all_fork[i + 1];
		philos[i].r_fork = all->all_fork[(i + 2) % all->nbr_philo];
	}
}
void	init_forks(t_all_philo *all)
{
	int	i;

	i = -1;
	while (++i < all->nbr_philo)
	{
		all->all_fork[i].id_fork = i + 1;
		pthread_mutex_init(&all->all_fork[i].fork, NULL);
	}
}

void	init_all(t_all_philo *all, char **av)
{
	all->nbr_philo = ft_atol(av[1]);
	all->time_to_die = ft_atol(av[2]);
	all->time_to_eat = ft_atol(av[3]);
	all->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		all->max_meal = ft_atol(av[5]);
	else
		all->max_meal = -1;
	all->begin_meal = false;
	all->end_meal = false;
	all->all_philo = malloc(all->nbr_philo * sizeof (t_philo));
	if (!all->all_philo)
		exit_err("error malloc!");
	all->all_fork = malloc(all->nbr_philo * sizeof(t_fork));
	if (!all->all_fork)
		exit_err("error malloc!");
	init_forks(all);
	init_philo(all);
	pthread_mutex_init(&all->lock, NULL);
	pthread_mutex_init(&all->write_lock, NULL);
}

void	threads(t_all_philo *all)
{
	int	i;

	i = -1;
	while (++i < all->nbr_philo)
		if (pthread_create(&all->all_philo[i].philo_thread, NULL, philo_routine, (void *)&all->all_philo[i]))
			write(2, "Error creating a mutex!\n", 24);// a modifier
	set_long(&all->lock, &all->start_time, now());
	set_bool(&all->lock, &all->begin_meal, true);
	// all->start_time = now();
	// monitoring_all(all);
	i = -1;
	while (++i < all->nbr_philo)
		if (pthread_join(all->all_philo[i].philo_thread, NULL))
			write(2, "Error join a mutex!\n", 20);// a modifier
}
