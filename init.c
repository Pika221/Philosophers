#include "philosophers.h"

int	init_program(int ac, char **av, t_args *args)
{
	args->philo_count = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args ->meal_count = -1;
	args->death = 0;
	args->start_time = get_time();
	if (ac == 6)
		args ->meal_count = ft_atoi(av[5]);
	if (pthread_mutex_init(&args->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&args->death_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	create_philos(t_args *args, t_philo **philos, pthread_mutex_t **forks)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * args->philo_count);
	*forks = malloc(sizeof(pthread_mutex_t) * args->philo_count);
	if(!*forks || !*philos)
		return (1);
	i = -1;
	while (++i < args->philo_count)
		if (pthread_mutex_init(&(*forks)[i], NULL) != 0)
			return (1);
	i = -1;
	while (++i < args->philo_count)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].args = args;
		(*philos)[i].meal_count = 0;
		(*philos)[i].last_meal = get_time();
		(*philos)[i].left_fork = &(*forks)[i];
		(*philos)[i].right_fork = &(*forks)[(i + 1) % args->philo_count];
	}
	return (0);
}

