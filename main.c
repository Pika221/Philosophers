#include "philosophers.h"

void join_threads(t_philo *philos, int philo_count)
{
    int i;

    i = 0;
    while (i < philo_count)
    {
        pthread_join(philos[i].thread, NULL);
        i++;
    }
}


int main(int ac, char **av)
{
    t_args          args;
    t_philo         *philos;
    pthread_mutex_t *forks;

    if (check_error(ac, av))
	{
		printf("%s", check_error(ac, av));
        return (1);
	}
    if (init_program(ac, av, &args))
    {
	    write(2, "Program initializing failed\n", 28);
        return (1);
	}
    if (create_philos(&args, &philos, &forks))
    {
        write(2, "Philo creating failed\n", 22);
        return (1);
    }
    if (start_threads(philos, args.philo_count))
    {
        write(2, "Thread creation failed\n", 23);
        cleanup(philos, forks, args.philo_count, &args);
        free(philos);
        free(forks);
        return (1);
    }
    monitor(philos, &args);
    join_threads(philos, args.philo_count);
    cleanup(philos, forks, args.philo_count, &args);
    free(philos);
    free(forks);
    return (0);
}
