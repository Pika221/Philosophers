#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define PHILO_MAX 200
# define PHILO_MIN 1
# define MAX_INT 2147483647

typedef struct s_args
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_count;
	long			start_time;
	int				death;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
}	t_args;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				meal_count;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_args			*args;
}	t_philo;

char	*check_error(int ac, char **av);
long    ft_atoi(char *s);
long	get_time(void);
void	ft_usleep(long duration);
int		init_program(int ac, char **av, t_args *args);
int	create_philos(t_args *args, t_philo **philos, pthread_mutex_t **forks);

#endif