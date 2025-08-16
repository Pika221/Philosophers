/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hialpagu <hialpagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:20:18 by hialpagu          #+#    #+#             */
/*   Updated: 2025/08/10 16:20:18 by hialpagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	death_status(t_args *data, size_t idx)
{
	size_t	current_time;
	size_t	last_meal_time;
	bool	must_eat_status;
	size_t	time_diff;
	size_t	i;

	pthread_mutex_lock(&data->status_mutex);
	current_time = get_time();
	last_meal_time = data->philos[idx].last_meal;
	must_eat_status = data->philos[idx].must_eat;
	time_diff = current_time - last_meal_time;
	if (time_diff > data->philos[idx].time_to_die && must_eat_status)
	{
		data->finished = true;
		i = 0;
		while (i < data->philo_count)
			data->philos[i++].alive = false;
		pthread_mutex_unlock(&data->status_mutex);
		print_action(&data->philos[idx], "died");
		return (false);
	}
	pthread_mutex_unlock(&data->status_mutex);
	return (true);
}

static bool	all_done_and_finalize(t_args *p)
{
	size_t	i;

	i = 0;
	while (i < p->philo_count)
		if (p->philos[i++].must_eat)
			return (false);
	i = 0;
	while (i < p->philo_count)
		p->philos[i++].alive = false;
	p->finished = true;
	return (true);
}

bool	meal_status(t_args *philo, size_t idx)
{
	bool	all_done;

	pthread_mutex_lock(&philo->status_mutex);
	if (philo->philos[idx].meal_count != -1
		&& philo->philos[idx].finished_meals >= philo->philos[idx].meal_count
		&& philo->philos[idx].alive)
		philo->philos[idx].must_eat = false;
	all_done = all_done_and_finalize(philo);
	pthread_mutex_unlock(&philo->status_mutex);
	return (!all_done);
}

void	check_status(t_args *data)
{
	size_t	i;
	bool	program_finished;

	while (1)
	{
		i = 0;
		pthread_mutex_lock(&data->status_mutex);
		program_finished = data->finished;
		pthread_mutex_unlock(&data->status_mutex);
		if (program_finished)
			break ;
		while (i < data->philo_count)
		{
			if (!death_status(data, i))
				return ;
			if (data->philos[i].meal_count != -1)
				if (!meal_status(data, i))
					return ;
			i++;
		}
		usleep(500);
	}
}
