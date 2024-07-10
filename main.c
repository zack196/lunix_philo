# include "philo.h"

int	main(int ac, char **av)
{
	t_all_philo	all;

	if ((ac != 5 && ac != 6) || !chec_arg(av))
		return (printf("arg non valid!\n"));
	init_all(&all, av);
	threads(&all);
} 