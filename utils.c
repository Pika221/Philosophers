/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hialpagu <hialpagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:15:37 by hialpagu          #+#    #+#             */
/*   Updated: 2025/06/21 20:29:02 by hialpagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atoi(const char *str)
{
	long	num;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		++i;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num *= 10;
		num = num + (str[i] - '0');
		++i;
		if (num > MAX_INT)
			break ;
	}
	return (num * sign);
}

void	print_status(t_philo *philo, char *message)
{
	int		finished;

	pthread_mutex_lock(&philo->args->status_mutex);
	finished = philo->args->finished;
	pthread_mutex_unlock(&philo->args->status_mutex);
	if (finished)
		return ;
	pthread_mutex_lock(&philo->args->print_mutex);
	printf("%d %d %s", get_time() - philo->args->starting_time, philo->id + 1,
		message);
	pthread_mutex_unlock(&philo->args->print_mutex);
}

int	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t mls)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < mls)
		usleep(500);
}
