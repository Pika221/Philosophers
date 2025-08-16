/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hialpagu <hialpagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:55:21 by hialpagu          #+#    #+#             */
/*   Updated: 2025/08/10 19:08:02 by hialpagu         ###   ########.fr       */
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
			return (-1);
	}
	return (num * sign);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(t_philo *philo, size_t mls)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < mls)
	{
		pthread_mutex_lock(&philo->data->status_mutex);
		if (philo->data->finished)
		{
			pthread_mutex_unlock(&philo->data->status_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->status_mutex);
		usleep(500);
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	print_action(t_philo *philo, char *message)
{
	t_args	*p;

	p = philo->data;
	pthread_mutex_lock(&p->status_mutex);
	if (p->finished && ft_strcmp(message, "died") != 0)
	{
		pthread_mutex_unlock(&p->status_mutex);
		return ;
	}
	pthread_mutex_lock(&p->print_mutex);
	if (!p->finished || ft_strcmp(message, "died") == 0)
		printf("%zu %zu %s\n", get_time() - p->starting_time,
			philo->id + 1, message);
	pthread_mutex_unlock(&p->print_mutex);
	pthread_mutex_unlock(&p->status_mutex);
}
