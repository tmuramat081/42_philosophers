#include "philosophers.h"

long	gettime_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) < 0)
		exit(1);
	return ((long)(tv.tv_sec * 1000) + (long)(tv.tv_usec / 1000));
}

long	get_elapsed_time(long start_ms, long end_ms)
{
	return (end_ms - start_ms);
}

void	put_timestamp(char *string, t_philosopher *philo)
{
	long	elapsed_time;
	long	now;

	now = gettime_ms();
	elapsed_time = get_elapsed_time(philo->start_time, now);
	printf("%ld %zu %s\n", elapsed_time, philo->id + 1, string);
}
