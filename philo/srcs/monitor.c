#include "philosophers.h"


int	dead_timestamp(char *string, t_philosopher *philo)
{
	long	elapsed_time;
	long	now;

	now = gettime_ms();
	elapsed_time = get_elapsed_time(philo->started_at, now);
	pthread_mutex_lock(&philo->monitor->io);
	printf("%ld %zu %s\n", elapsed_time, philo->id + 1, string);
	pthread_mutex_unlock(&philo->monitor->io);
	return (1);
}



void	*checker(void *p_monitor)
{
	t_philosopher	*philos;
	t_monitor		*monitor;
	long			elapsed;
	size_t			i;

	monitor = (t_monitor *)p_monitor;
	philos = monitor->philos;
	while (true)
	{
		i = 0;
		while (i < monitor->num_of_philos)
		{
			elapsed = get_elapsed_time(philos[i].last_eat_at, gettime_ms());
			if (elapsed > (long)monitor->time_to_die)
			{
				monitor->is_any_died = true;
				dead_timestamp(MSG_DIED, &philos[i]);
				return (NULL);
			}
			i++;
		}
	}
}

