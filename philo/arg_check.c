/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hialpagu <hialpagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:20:30 by hialpagu          #+#    #+#             */
/*   Updated: 2025/08/10 16:20:30 by hialpagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_is_digit(int a)
{
	if (a >= '0' && a <= '9')
		return (0);
	return (1);
}

static int	check_is_num(int ac, char **av)
{
	int	j;

	j = 0;
	while (av[--ac][j] && ac > 0)
	{
		if (av[ac][j] == '-' || av[ac][j] == '+')
			j++;
		while (av[ac][j])
		{
			if (ft_is_digit(av[ac][j]))
			{
				printf("Invalid arguments!\n");
				return (1);
			}
			j++;
		}
		j = 0;
	}
	return (0);
}

static int	check_is_int(int ac, char **av)
{
	int	num;

	while (--ac && ac > 0)
	{
		num = ft_atoi(av[ac]);
		if (num <= 0 || num > MAX_INT)
		{
			printf("Please enter a positive number less than MAX_INT.\n");
			return (1);
		}
	}
	return (0);
}

int	arg_check(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Invalid argument count!\n");
		return (1);
	}
	if (check_is_num(ac, av))
		return (1);
	if (check_is_int(ac, av))
		return (1);
	if (ft_atoi(av[1]) < MIN_PHILO)
	{
		printf("Min philosophers count is 1!\n");
		return (1);
	}
	if (ft_atoi(av[1]) > MAX_PHILO)
	{
		printf("Max philosophers count is 200!\n");
		return (1);
	}
	return (0);
}
