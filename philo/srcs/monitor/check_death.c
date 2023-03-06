#include "philosophers.h"

bool	is_philo_dead(t_monitor *monitor, t_philosopher *philos)
{
	long	elapsed;
	size_t	i;

	i = 0;
	while (i < monitor->num_of_philos)
	{
		pthread_mutex_lock(&philos[i].mutex);
		elapsed = get_elapsed_time(philos[i].last_eat_at, gettime_ms());
		if (elapsed > (long)monitor->time_to_die)
		{
			monitor->is_sim_over = true;
			dead_timestamp(MSG_DIED, &philos[i]);
			pthread_mutex_unlock(&philos[i].mutex);
			return (true);
		}
		pthread_mutex_unlock(&philos[i].mutex);
		i++;
	}
	return (false);
}
