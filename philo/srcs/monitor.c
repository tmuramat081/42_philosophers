#include "philosophers.h"

void	*monitor(void *p_waiter)
{
	t_philosopher	*philos;
	t_arbitrator	*waiter;
	size_t			i;

	waiter = (t_arbitrator *)p_waiter;
	philos = waiter->philos;
	while (true)
	{
		i = 0;
		while (i < waiter->num_of_philos)
		{
			if (gettime_ms() - philos[i].time_last_eaten > (long)waiter->time_to_eat)
			{
				put_timestamp(MSG_DIED, &philos[i]);
				// pthread_mutex_lock(&philos[i].mutex);
				return ((void *)0);
			}
			i++;
		}
	}
}
