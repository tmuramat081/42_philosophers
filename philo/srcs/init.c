#include "philosophers.h"

long	gettime_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) < 0)
		exit(1);
	return ((long)(tv.tv_sec * 1000) + (long)(tv.tv_usec / 1000));
}

t_arbitrator	*init_waiter(t_philo_dto dto)
{
	t_arbitrator	*waiter;

	waiter = malloc(sizeof(t_arbitrator));
	waiter->start_time = gettime_ms();
	waiter->num_of_philos = dto.num_of_philosophers;
	waiter->time_to_die = dto.time_to_die;
	waiter->time_to_sleep = dto.time_to_sleep;
	waiter->time_to_eat = dto.time_to_eat;
	waiter->num_of_eating = dto.num_of_eating;
	return (waiter);
}

t_philosopher	*init_philosophers(t_philo_dto input)
{
	t_philosopher	*philos;
	size_t			i;

	philos = malloc(sizeof(t_philosopher) * input.num_of_philosophers);
	i = 0;
	while (i < input.num_of_philosophers)
	{
		philos[i].start_time = gettime_ms();
		philos[i].id = i;
		philos[i].fork_left = (i + 1) % input.num_of_philosophers;
		philos[i].fork_right = i;
		i++;
	}
	return (philos);
}
