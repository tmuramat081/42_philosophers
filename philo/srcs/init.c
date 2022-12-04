#include "philosophers.h"

longlong gettime()
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	
}

t_arbitrator	*init_waiter(t_dto dto)
{
	t_arbitrator	*waiter;

	waiter = malloc(sizeof(t_arbitrator));
	waiter->start_time = gettimeofday()
	waiter->num_of_philos = dto.num_of_philosophers;
	waiter->time_to_die = dto.time_to_die;
	waiter->time_to_sleep = dto.time_to_sleep;
	waiter->time_to_eat = dto.time_to_eat;
	waiter->num_of_eating = dto.num_of_eating;
	return (waiter);
}

t_philosopher	*init_philosophers(t_dto dto)
{
	t_philosopher	*philos;
	size_t	i;

	philos = malloc(sizeof(t_philosopher) * dto.num_of_philosophers);
	i = 0;
	while (i < dto.num_of_philosophers)
	{
		philos[i].id = i;
		i++;
	}
	return (philos);
}
