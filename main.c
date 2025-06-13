#include "philosophers.h"

int main(int ac, char **av)
{
    t_args          args;
    t_philo         *philos;
    pthread_mutex_t *forks;

    // error yoksa programı başlat error varsa hata çıktısı ver
    if (check_error(ac, av))
	{
		printf("%s", check_error(ac, av));
        return (1); //start_program(ac, av, program);
	}
    if (init_program(ac, av, &args))
    {
	    write(2, "Program initializing is failed\n", 31);
        return (1); //start_program(ac, av, program);
	}
    if (create_philos(&args, &philos, &forks))
    {
        write(2, "Philo creating is failed\n", 25);
        return (1);
    }
    printf("succsess\n");
    free (philos);
    free (forks);
    return (0);
}
/*int main(void)
{
	long start = get_time();
	printf("Başlangıç: %ld\n", start);
	ft_usleep(1500); // 1.5 saniye bekle
	printf("Bitiş: %ld\n", get_time());
	return (0);
}*/