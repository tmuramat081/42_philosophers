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

int	put_timestamp(char *string, t_philosopher *philo)
{
	long	elapsed_time;
	long	now;

	now = gettime_ms();
	elapsed_time = get_elapsed_time(philo->started_at, now);
	if (philo->monitor->is_any_died == true)
	{
		pthread_mutex_unlock(&philo->monitor->io);
		return (0);
	}
	pthread_mutex_lock(&philo->monitor->io);
	printf("%ld %zu %s\n", elapsed_time, philo->id + 1, string);
	pthread_mutex_unlock(&philo->monitor->io);
	return (1);
}
