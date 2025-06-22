/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <hialpagu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:15:17 by hialpagu          #+#    #+#             */
/*   Updated: 2025/06/22 20:55:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	mutex_init(t_args *args)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&args->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&args->status_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&args->print_mutex);
		return (1);
	}
	while (i < args->philo_count)
	{
		if (pthread_mutex_init(&args->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&args->forks[i]);
			pthread_mutex_destroy(&args->print_mutex);
			pthread_mutex_destroy(&args->status_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	philo(int ac, char **av, t_args *arg, int i)
{
	arg->philo[i].id = i;
	arg->philo[i].time_to_die = ft_atoi(av[2]);
	arg->philo[i].time_to_eat = ft_atoi(av[3]);
	arg->philo[i].time_to_sleep = ft_atoi(av[4]);
	arg->philo[i].last_meal = get_time();
	if (arg->philo[i].last_meal == 0)
		return (1);
	arg->philo[i].meal_count = -1;
	if (ac == 6)
		arg->philo[i].meal_count = ft_atoi(av[5]);
	arg->philo[i].finished_meals = 0;
	arg->philo[i].must_eat = 1;
	arg->philo[i].alive = 1;
	arg->philo[i].args = arg;
	if (arg->forks)
	{
		arg->philo[i].right_fork = &arg->forks[arg->philo[i].id];
		arg->philo[i].left_fork = &arg->forks[(arg->philo[i].id + 1)
			% arg->philo_count];
	}
	return (0);
}

static int	philo_init(int ac, char **av, t_args *arg)
{
	int	i;

	arg->philo = malloc(arg->philo_count * sizeof(t_philo));
	if (!arg->philo)
		return (1);
	i = 0;
	while (i < arg->philo_count)
	{
		if (philo(ac, av, arg, i))
			return (1);
		i++;
	}
	return (0);
}

int	init_args(int ac, char **av, t_args *args)
{
	args->philo_count = ft_atoi(av[1]);
	args->finished = 0;
	args->forks = malloc(sizeof(pthread_mutex_t) * args->philo_count);
	if (!args->forks)
		return (1);
	if (mutex_init(args))
		return (1);
	if (philo_init(ac, av, args))
		return (1);
	args->starting_time = get_time();
	return (0);
}
