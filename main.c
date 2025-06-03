#include "philo.h"
//pthread_mutex_destroy ve freeleme yapılacak
static  void    free_program(t_program *program)
{

}
static int free_n_exit(int ac, char **av, t_program *program)
{
    if (start_program(ac, av, program)) //yapılacak
        printf("Program couldn't initialize.\n");
    else if (create_philos(program)) //yapılacak
        printf("Program couldn't create philosophers.\n");
    free_program(program); //yapılacak
    return (1);
}

int main(int ac, char **av)
{
    t_program   *program;

    // error yoksa programı başlat error varsa hata çıktısı ver
    if (!check_error(ac, av))
        printf("succsess\n"); //start_program(ac, av, program);
    else
        return (1);
    //if (start_program(ac, av, program))
    //    free_n_exit();    
    //if (create_philos(program))
    //    free_n_exit();
    //free_program(program);
    return (0);
}