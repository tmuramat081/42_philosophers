#include "philosophers.h"

t_arbitrator	*init_waiter(t_philo_dto input)
{
	t_arbitrator	*waiter;
	size_t			i;

	waiter = malloc(sizeof(t_arbitrator));
	waiter->start_time = gettime_ms();
	waiter->num_of_philos = input.num_of_philosophers;
	waiter->time_to_die = input.time_to_die;
	waiter->time_to_sleep = input.time_to_sleep;
	waiter->time_to_eat = input.time_to_eat;
	waiter->num_of_eat = input.num_of_eating;
	i = 0;
	while (i < input.num_of_philosophers)
		pthread_mutex_init(&waiter->forks[i++], NULL);
	return (waiter);
}

t_philosopher	*init_philosophers(t_philo_dto input, t_arbitrator *waiter)
{
	t_philosopher	*philos;
	size_t			i;

	philos = malloc(sizeof(t_philosopher) * input.num_of_philosophers);
	i = 0;
	while (i < input.num_of_philosophers)
	{
		philos[i].start_time = gettime_ms();
		philos[i].id = i;
		philos[i].fork_left = waiter->forks[i + 1];
		philos[i].fork_right = waiter->forks[i];
		philos[i].cnt_eat = 0;
		i++;
	}
	return (philos);
}
