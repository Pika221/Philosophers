/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <hialpagu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:09:17 by marvin            #+#    #+#             */
/*   Updated: 2025/06/13 16:09:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->args->print_mutex);
	printf("%ld %d has taken a fork\n",
		get_time() - philo->args->start_time, philo->id);
	pthread_mutex_unlock(&philo->args->print_mutex);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->args->print_mutex);
	printf("%ld %d has taken a fork\n",
		get_time() - philo->args->start_time, philo->id);
	printf("%ld %d is eating\n",
		get_time() - philo->args->start_time, philo->id);
	pthread_mutex_unlock(&philo->args->print_mutex);
	philo->last_meal = get_time();
	ft_usleep(philo->args->time_to_eat);
	philo->meal_count++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print_mutex);
	printf("%ld %d is sleeping\n",
		get_time() - philo->args->start_time, philo->id);
	pthread_mutex_unlock(&philo->args->print_mutex);
	ft_usleep(philo->args->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print_mutex);
	printf("%ld %d is thinking\n",
		get_time() - philo->args->start_time, philo->id);
	pthread_mutex_unlock(&philo->args->print_mutex);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
		
	while (1)
	{
		pthread_mutex_lock(&philo->args->death_mutex);
		if (philo->args->death)
		{
			pthread_mutex_unlock(&philo->args->death_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->args->death_mutex);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
