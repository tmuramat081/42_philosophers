#include "philosophers.h"

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
			if (elapsed > (long)monitor->time_to_eat)
			{
				monitor->is_any_died = true;
				put_timestamp(MSG_DIED, &philos[i]);
				return (NULL);
			}
			i++;
		}
	}
}

