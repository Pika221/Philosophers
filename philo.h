#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# define PHILO_MAX 200
# define PHILO_MIN 1
# define MAX_INT 2147483647

typedef struct s_philo
{
    size_t  time_to_sleep;
    size_t  time_to_eat;
    size_t  time_to_die;
    size_t  philo_id;
} t_philo;

typedef struct s_program
{
    t_philo     *philo;
} t_program;

int  check_error(int ac, char **av);

#endif