#include "philosophers.h"

void cleanup(t_philo *philos, pthread_mutex_t *forks, int philo_count, t_args *args)
{
    int i;

    i = 0;
    while (i < philo_count)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
    pthread_mutex_destroy(&args->print_mutex);
    pthread_mutex_destroy(&args->death_mutex);
}
