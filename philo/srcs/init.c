#include "philosophers.h"

t_arbitrator	init_waiter(t_philo_dto input)
{
	t_arbitrator	waiter;
	size_t			i;

	waiter.start_time = gettime_ms();
	waiter.num_of_philos = input.num_of_philos;
	waiter.time_to_die = input.time_to_die;
	waiter.time_to_eat = input.time_to_eat;
	waiter.time_to_sleep = input.time_to_sleep;
	waiter.num_of_eat = input.num_of_eating;
	pthread_mutex_init(&waiter.is_end, NULL);
	pthread_mutex_lock(&waiter.is_end);
	i = 0;
	while (i < input.num_of_philos)
		pthread_mutex_init(&waiter.forks[i++], NULL);
	return (waiter);
}

t_philosopher	*init_philosophers(t_philo_dto input, t_arbitrator *waiter)
{
	t_philosopher	*philos;
	size_t			i;

	philos = malloc(sizeof(t_philosopher) * PHILO_MAX);
	i = 0;
	while (i < input.num_of_philos)
	{
		philos[i].start_time = gettime_ms();
		philos[i].id = i;
		philos[i].fork_left = &waiter->forks[i + 1 % input.num_of_philos];
		philos[i].fork_right = &waiter->forks[i];
		philos[i].count_eaten = 0;
		philos[i].time_last_eaten = philos[i].start_time;
		philos[i].waiter = waiter;
		pthread_mutex_init(&philos[i].mutex, NULL);
		i++;
	}
	return (philos);
}
