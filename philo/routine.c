/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hialpagu <hialpagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:21:29 by hialpagu          #+#    #+#             */
/*   Updated: 2025/08/10 16:21:29 by hialpagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*alone(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->data->status_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->status_mutex);
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	ft_usleep(philo, philo->time_to_die);
	pthread_mutex_lock(&philo->data->status_mutex);
	philo->alive = 0;
	pthread_mutex_unlock(&philo->data->status_mutex);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void	*not_alone(void *data)
{
	t_philo	*philo;
	bool	alive;
	bool	must_eat;

	philo = (t_philo *)data;
	if (philo->id % 2 != 0)
		ft_usleep(philo, philo->time_to_eat / 2);
	while (1)
	{
		pthread_mutex_lock(&philo->data->status_mutex);
		alive = philo->alive;
		must_eat = philo->must_eat;
		pthread_mutex_unlock(&philo->data->status_mutex);
		if (!alive || !must_eat)
			break ;
		eating(philo);
		sleeping(philo);
	}
	return (NULL);
}

char	*start_routine(t_args *data)
{
	size_t	i;

	i = 0;
	if (data->philo_count == 1)
	{
		pthread_create(&data->philos[i].thread, NULL, alone, &data->philos[i]);
		i++;
	}
	while (i < data->philo_count)
	{
		pthread_create(&data->philos[i].thread, NULL,
			not_alone, &data->philos[i]);
		i++;
	}
	check_status(data);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (NULL);
}
