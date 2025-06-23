/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hialpagu <hialpagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:15:23 by hialpagu          #+#    #+#             */
/*   Updated: 2025/06/23 16:14:45 by hialpagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	free_n_exit(t_args *prog)
{
	int	i;

	i = 0;
	while (i < prog->philo_count)
	{
		pthread_mutex_destroy(&prog->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&prog->print_mutex);
	pthread_mutex_destroy(&prog->status_mutex);
	free(prog->forks);
	free(prog->philo);
}

int	main(int ac, char **av)
{
	t_args	args;

	if (arg_check(ac, av))
		return (1);
	if (init_args(ac, av, &args))
		return (1);
	start_routine(&args);
	free_n_exit(&args);
	return (0);
}
