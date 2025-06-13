#include "philosophers.h"

static int ft_isdigit(int a)
{
    if (a >= '0' && a <= '9')
        return (1);
    return (0);
}

static int check_num(char *a)
{
    if (!*a)
        return (0);
    if (*a == '+' || *a == '-')
        a++;
    while (*a)
    {
        if (!ft_isdigit(*a))
            return (0);
        a++;
    }
    return (1);
}

long    ft_atoi(char *s)
{
    long    num;
    int     sign;
    int     i;

    num = 0;
    sign = 1;
    i = 0;
    while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ')
        i++;
    if (s[i] == '+' || s[i] == '-')
        if (s[i] == '-')
            sign = -1;
    while (s[i] >= '0' && s[i] <= '9')
    {
        num = (num * 10) + s[i] - '0';
        i++;
        if (num > MAX_INT)
            break;
    }
    return (num * sign);
}
char  *check_error(int ac, char **av)
{
    long num;

    if (ac != 5 && ac != 6)
        return ("Invalid arguments count.\n");
    while (ac > 0 && --ac)
    {
        if (!check_num(av[ac]))
            return ("Invalid arguments\n");
        num = ft_atoi(av[ac]);
        if (ac == 1 && num > PHILO_MAX)
            return ("Max philosopher count is 200.\n");
        if (ac == 1 && num < PHILO_MIN)
            return("Min philosophers count is 1.\n");
        if (num < 1 || num > MAX_INT)
            return("Please enter less than MAX_INT and positive number.\n");
    }
    return (NULL);
}
