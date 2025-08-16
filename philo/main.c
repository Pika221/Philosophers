/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hialpagu <hialpagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:21:12 by hialpagu          #+#    #+#             */
/*   Updated: 2025/08/10 16:21:14 by hialpagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	free_n_exit(t_args *data)
{
	size_t	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->status_mutex);
	free(data->forks);
	free(data->philos);
	free(data);
}

int	main(int ac, char **av)
{
	t_args	*data;
	char	*msg;

	if (arg_check(ac, av))
		return (1);
	msg = args_init(ac, av, &data);
	if (msg)
	{
		printf("%s\n", msg);
		free_n_exit(data);
		return (1);
	}
	msg = start_routine(data);
	if (msg)
	{
		printf("%s\n", msg);
		free_n_exit(data);
		return (1);
	}
	free_n_exit(data);
	return (0);
}
