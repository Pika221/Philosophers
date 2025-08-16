/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hialpagu <hialpagu@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:20:45 by hialpagu          #+#    #+#             */
/*   Updated: 2025/08/15 17:54:12 by hialpagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static pthread_mutex_t	*mutex_init(t_args *data)
{
	pthread_mutex_t	*mutex;
	size_t			i;

	i = 0;
	mutex = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (mutex == NULL)
		return (NULL);
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&mutex[i], NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&mutex[i]);
			}
			free(mutex);
			return (NULL);
		}
		i++;
	}
	return (mutex);
}

static void	fork_number(t_args *data, t_philo *philo)
{
	philo->right_fork = &data->forks[philo->id];
	philo->left_fork = &data->forks[(philo->id + 1) % data->philo_count];
}

char	*philo(int ac, char **av, t_args *data, int i)
{
	data->philos[i].id = i;
	data->philos[i].time_to_die = ft_atoi(av[2]);
	data->philos[i].time_to_eat = ft_atoi(av[3]);
	data->philos[i].time_to_sleep = ft_atoi(av[4]);
	data->philos[i].last_meal = 0;
	data->philos[i].finished_meals = 0;
	data->philos[i].meal_count = -1;
	if (ac == 6)
		data->philos[i].meal_count = ft_atoi(av[5]);
	data->philos[i].data = data;
	data->philos[i].alive = 1;
	data->philos[i].must_eat = 1;
	fork_number(data, &data->philos[i]);
	return (NULL);
}

char	*philos_init(int ac, char **av, t_args *data)
{
	size_t	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
		return ("malloc failed.");
	while (i < data->philo_count)
	{
		if (philo(ac, av, data, i))
			return ("creating philo failed.");
		i++;
	}
	return (NULL);
}

char	*args_init(int ac, char **av, t_args **data)
{
	size_t	i;

	*data = malloc(sizeof(t_args));
	if (!*data)
		return ("failed to allocate.");
	(*data)->philo_count = ft_atoi(av[1]);
	(*data)->finished = 0;
	(*data)->starting_time = get_time();
	if (pthread_mutex_init(&(*data)->status_mutex, NULL) != 0
		|| pthread_mutex_init(&(*data)->print_mutex, NULL) != 0)
		return ("mutex failed.");
	(*data)->forks = mutex_init(*data);
	if (!(*data)->forks)
	{
		pthread_mutex_destroy(&(*data)->print_mutex);
		pthread_mutex_destroy(&(*data)->status_mutex);
		return ("forks couldn't create.");
	}
	if (philos_init(ac, av, *data))
		return ("philos couldn't initilaze.");
	i = 0;
	while (i < (*data)->philo_count)
		(*data)->philos[i++].last_meal = (*data)->starting_time;
	return (NULL);
}
