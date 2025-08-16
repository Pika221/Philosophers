/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hialpagu <hialpagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:21:00 by hialpagu          #+#    #+#             */
/*   Updated: 2025/08/10 16:21:00 by hialpagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	taking_forks(t_philo *philo)
{
	if (philo->id == philo->data->philo_count - 1)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
}

void	leaving_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	eating(t_philo *philo)
{
	taking_forks(philo);
	pthread_mutex_lock(&philo->data->status_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->status_mutex);
	print_action(philo, "is eating");
	ft_usleep(philo, philo->time_to_eat);
	leaving_forks(philo);
	pthread_mutex_lock(&philo->data->status_mutex);
	if (philo->meal_count != -1)
		philo->finished_meals++;
	pthread_mutex_unlock(&philo->data->status_mutex);
}

void	sleeping(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo, philo->time_to_sleep);
	print_action(philo, "is thinking");
	if (philo->data->philo_count % 2 == 1)
		ft_usleep(philo, philo->time_to_eat);
}
