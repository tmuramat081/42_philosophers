#include "philosophers.h"

bool	is_philo_full(t_monitor *monitor, t_philosopher *philos)
{
	size_t	i;
	size_t	cnt_full;

	if (monitor->num_of_eat == -1)
		return (false);
	i = 0;
	cnt_full = 0;
	while (i < monitor->num_of_philos)
	{
		pthread_mutex_lock(&philos[i].mutex);
		if (philos[i].count_eaten >= (size_t)monitor->num_of_eat)
		{
			cnt_full++;
		}
		pthread_mutex_unlock(&philos[i].mutex);
		i++;
	}
	if (cnt_full >= monitor->num_of_philos)
	{
		pthread_mutex_lock(&philos[i].mutex);
		monitor->is_sim_over = true;
		pthread_mutex_unlock(&philos[i].mutex);
		return (true);
	}
	return (false);
}