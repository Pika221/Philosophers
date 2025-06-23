/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hialpagu <hialpagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:15:33 by hialpagu          #+#    #+#             */
/*   Updated: 2025/06/23 18:20:30 by hialpagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*survivor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork\n");
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void	*staying_alive(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (1)
	{
		pthread_mutex_lock(&philo->args->status_mutex);
		if (!philo->alive || !philo->must_eat)
		{
			pthread_mutex_unlock(&philo->args->status_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->args->status_mutex);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	start_routine(t_args	*prog)
{
	int	i;

	i = 0;
	if (prog->philo_count == 1)
	{
		pthread_create(&prog->philo[i].thread, NULL,
			survivor, &prog->philo[i]);
		i++;
	}
	while (i < prog->philo_count)
	{	
		pthread_create(&prog->philo[i].thread, NULL,
			staying_alive, &prog->philo[i]);
		i++;
	}
	routine(prog);
	i = 0;
	while (i < prog->philo_count)
	{
		pthread_join(prog->philo[i].thread, NULL);
		i++;
	}
}
