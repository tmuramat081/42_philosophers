#include "philosophers.h"

long	gettime_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) < 0)
		exit(1);
	return ((long)(tv.tv_sec * 1000) + (long)(tv.tv_usec / 1000));
}

long	get_elapsed_time_ms(long start_ms)
{
	t_timeval	now;
	long		now_ms;

	if (gettimeofday(&now, NULL) < 0)
		exit(1);
	now_ms = (long)(now.tv_sec * 1000) + (long)(now.tv_usec / 1000);
	return (now_ms - start_ms);
}

void	put_timestamp(char *string, t_philosopher *philo)
{
	long	elapsed_time;

	elapsed_time = get_elapsed_time_ms(philo->start_time);
	printf("%ld %zu %s\n", elapsed_time, philo->id, string);
}
