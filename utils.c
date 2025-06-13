#include "philosophers.h"

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write (2, "gettimeofday failed\n", 21);
		return (0);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(long duration)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < duration)
		usleep(100);
}