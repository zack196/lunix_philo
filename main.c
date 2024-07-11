#include "philo.h"

void	philo_init(t_table_philo *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_philo)
	{
		table->all_philos[i].philo_id = i + 1;
		table->all_philos[i].table = table;
		table->all_philos[i].r_fork = &table->all_fork[i];
		table->all_philos[i].l_fork = &table->all_fork[(i + 1) % table->nbr_philo];
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
	if (pthread_mutex_init(&table->table_lock, NULL) 
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
	if (av[5])
		table->max_nbr_meals = ft_atol(av[5]);
	else
		table->max_nbr_meals = -1;
	table->all_fork = malloc(sizeof (pthread_mutex_t) * table->nbr_philo);
	if (!table->all_fork)
		return(0);
	table->all_philos = malloc(sizeof (t_philo) * table->nbr_philo);
	if (!table->all_philos)
		return(0);
	philo_init(table);
	if (init_mutex(table))
		return (0);
	return (table->nbr_philo && table->t2d && table->t2e && table->t2s);
}

int	philosophers(t_table_philo *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_philo)
		if (pthread_create(&table->all_philos[i].philo_thread, NULL, philo_routine, (void *)&table->all_philos[i]))
			return (printf("error creating thread\n"));
	table->start_time = now();
	table->begin_simulation = true;
	i = -1;
	while (++i < table->nbr_philo)
		if (pthread_join(table->all_philos[i].philo_thread, NULL))
			return (printf("error creating thread\n"));
	return (0);
}

int	main(int ac, char **av)
{
	t_table_philo	table;

	if ((ac != 5 && ac != 6) || !init_table(&table, av))
		return (1);
	if (philosophers(&table))
		return (1);
}