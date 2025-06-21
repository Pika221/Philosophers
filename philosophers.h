/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hialpagu <hialpagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:15:29 by hialpagu          #+#    #+#             */
/*   Updated: 2025/06/21 20:15:29 by hialpagu         ###   ########.fr       */
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

typedef struct s_philo	t_philo;
typedef struct s_args	t_args;

struct s_philo
{
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				finished_meals;
	int				meal_count;
	int				last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	t_args			*args;
	int				alive;
	int				must_eat;
};

struct s_args
{
	t_philo			*philo;
	int				philo_count;
	int				starting_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	status_mutex;
	int				finished;

};

long	ft_atoi(const char *str);
int		arg_check(int ac, char **av);
int		init_args(int ac, char **av, t_args *args);
void	start_routine(t_args	*prog);
void	print_status(t_philo *philo, char *message);
int		get_time(void);
void	ft_usleep(size_t mls);
void	*survivor(void *arg);
void	*staying_alive(void *arg);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
int		check_death(t_args *arg, int index);
int		check_meal(t_args *arg, int index);
void	routine(t_args *arg);

#endif