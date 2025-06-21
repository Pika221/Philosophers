/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hialpagu <hialpagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:15:26 by hialpagu          #+#    #+#             */
/*   Updated: 2025/06/21 20:29:40 by hialpagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	routine(t_args *arg)
{
	int	i;

	while (!arg->finished)
	{
		i = 0;
		while (i < arg->philo_count)
		{
			if (!check_death(arg, i))
				break ;
			if (!check_meal(arg, i))
				break ;
			i++;
		}
		ft_usleep(1);
	}
}

int	check_meal(t_args *arg, int index)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&arg->status_mutex);
	if (arg->philo[index].meal_count != -1)
		if (arg->philo[index].finished_meals == arg->philo[index].meal_count)
			arg->philo[index].must_eat = 0;
	while (i < arg->philo_count && !arg->philo[i].must_eat)
		i++;
	if (i == arg->philo_count)
		arg->finished = 1;
	pthread_mutex_unlock(&arg->status_mutex);
	if (i != arg->philo_count)
		return (1);
	return (0);
}

int	check_death(t_args *arg, int index)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&arg->status_mutex);
	if (get_time() - arg->philo[index].last_meal > arg->philo[index].time_to_die
		&& arg->philo[index].must_eat)
	{
		pthread_mutex_unlock(&arg->status_mutex);
		print_status(&arg->philo[index], "died\n");
		pthread_mutex_lock(&arg->status_mutex);
		arg->finished = 1;
		while (i < arg->philo_count)
			arg->philo[i++].alive = 0;
		pthread_mutex_unlock(&arg->status_mutex);
		return (0);
	}
	pthread_mutex_unlock(&arg->status_mutex);
	return (1);
}
