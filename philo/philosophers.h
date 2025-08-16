/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hialpagu <hialpagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:21:39 by hialpagu          #+#    #+#             */
/*   Updated: 2025/08/13 15:11:22 by hialpagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define MIN_PHILO 1
# define MAX_PHILO 200
# define MAX_INT 2147483647

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_philo	t_philo;
typedef struct s_args	t_args;

struct s_philo
{
	pthread_t		thread;
	size_t			id;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	long			meal_count;
	long			finished_meals;
	bool			alive;
	bool			must_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_args			*data;
};

struct s_args
{
	t_philo			*philos;
	size_t			philo_count;
	size_t			starting_time;
	bool			finished;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	status_mutex;
};

long	ft_atoi(const char *str);
size_t	get_time(void);
void	ft_usleep(t_philo *philo, size_t mls);
int		ft_strcmp(const char *s1, const char *s2);
void	print_action(t_philo *philo, char *message);
int		arg_check(int ac, char **av);
char	*args_init(int ac, char **av, t_args **data);
char	*philos_init(int ac, char **av, t_args *data);
char	*philo(int ac, char **av, t_args *data, int i);
char	*start_routine(t_args *data);
void	*alone(void *data);
void	*not_alone(void *data);
void	taking_forks(t_philo *philo);
void	leaving_forks(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	check_status(t_args *data);
bool	death_status(t_args *data, size_t id);
bool	meal_status(t_args *data, size_t idx);

#endif