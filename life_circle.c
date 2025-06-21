/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hialpagu <hialpagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:15:20 by hialpagu          #+#    #+#             */
/*   Updated: 2025/06/21 20:28:33 by hialpagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork\n");
	}
	print_status(philo, "is eating\n");
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(&philo->args->status_mutex);
	philo->last_meal = get_time();
	philo->finished_meals++;
	pthread_mutex_unlock(&philo->args->status_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping\n");
	ft_usleep(philo->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_status(philo, "is thinking\n");
}
