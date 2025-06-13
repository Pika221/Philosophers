#include "philosophers.h"

int	check_death(t_philo *philo, t_args *args)
{
	long	now;

	now = get_time();
	pthread_mutex_lock(&args->death_mutex);
	if ((now - philo->last_meal) > args->time_to_die)
	{
		args->death = 1;
		pthread_mutex_lock(&args->print_mutex);
		printf("%ld %d died\n", now - args->start_time, philo->id);
		pthread_mutex_unlock(&args->print_mutex);
		pthread_mutex_unlock(&args->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&args->death_mutex);
	return (0);
}

int	check_full(t_philo *philos, t_args *args)
{
	int	i;
	int	full;

	if (args->meal_count <= 0)
		return (0);
	full = 0;
	i = 0;
	while (i < args->philo_count)
	{
		pthread_mutex_lock(&args->death_mutex);
		if (philos[i].meal_count >= args->meal_count)
			full++;
		pthread_mutex_unlock(&args->death_mutex);
		i++;
	}
	if (full == args->philo_count)
	{
		pthread_mutex_lock(&args->death_mutex);
		args->death = 1;
		pthread_mutex_unlock(&args->death_mutex);
		return (1);
	}
	return (0);
}

int	monitor(t_philo *philos, t_args *args)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < args->philo_count)
		{
			if (check_death(&philos[i], args))
				return (1);
			i++;
		}
		if (check_full(philos, args))
			return (1);
		usleep(100);
	}
	return (0);
}
