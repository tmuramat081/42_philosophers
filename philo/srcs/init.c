#include "philosophers.h"

t_monitor	init_monitor(t_philo_dto input)
{
	t_monitor	monitor;
	size_t			i;

	monitor.started_at = gettime_ms();
	monitor.num_of_philos = input.num_of_philos;
	monitor.time_to_die = input.time_to_die;
	monitor.time_to_eat = input.time_to_eat;
	monitor.time_to_sleep = input.time_to_sleep;
	monitor.num_of_eat = input.num_of_eating;
	monitor.is_any_died = false;
	i = 0;
	while (i < input.num_of_philos)
		pthread_mutex_init(&monitor.forks[i++], NULL);
	pthread_mutex_init(&monitor.io, NULL);
	return (monitor);
}

t_philosopher	*init_philosophers(t_philo_dto input, t_monitor *monitor)
{
	t_philosopher	*philos;
	size_t			i;

	philos = malloc(sizeof(t_philosopher) * PHILO_MAX);
	i = 0;
	while (i < input.num_of_philos)
	{
		philos[i].started_at = gettime_ms();
		philos[i].id = i;
		philos[i].fork_left = &monitor->forks[i + 1 % input.num_of_philos];
		philos[i].fork_right = &monitor->forks[i];
		philos[i].count_eaten = 0;
		philos[i].last_eat_at = philos[i].started_at;
		philos[i].monitor = monitor;
		pthread_mutex_init(&philos[i].mutex, NULL);
		i++;
	}
	return (philos);
}
