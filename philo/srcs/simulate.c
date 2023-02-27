/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 00:36:29 by tmuramat          #+#    #+#             */
/*   Updated: 2023/02/24 00:54:57 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*lifecycle(void *p_philo)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)p_philo;
	while (true)
	{
		if (!do_eat(philo, philo->monitor)
			|| !do_sleep(philo, philo->monitor)
			|| !do_think(philo))
			break ;
	}
	return (NULL);
}

void	start_dinner(
	t_philosopher *philos, t_monitor *monitor, t_arbitrator *waiter)
{
	size_t		i;

	pthread_create(&waiter->thread_id, NULL, server, waiter);
	pthread_create(&monitor->thread_id, NULL, checker, monitor);
	pthread_detach(monitor->thread_id);
	i = 0;
	while (i < monitor->num_of_philos)
	{
		pthread_create(&philos[i].thread_id, NULL, lifecycle, &philos[i]);
		i++;
	}
}

void	end_dinner(t_philosopher *philos, t_monitor *monitor)
{
	size_t	i;

	i = 0;
	while (i < monitor->num_of_philos)
	{
		pthread_join(philos[i].thread_id, NULL);
		pthread_mutex_destroy(&philos[i].mutex);
		pthread_mutex_destroy(&monitor->forks[i]);
		i++;
	}
	free(philos);
}

void	simulate_problem(t_philo_dto input)
{
	t_monitor		monitor;
	t_philosopher	*philos;
	t_arbitrator	waiter;

	waiter = init_arbitrator(input);
	monitor = init_monitor(input);
	philos = init_philosophers(input, &monitor, &waiter);
	monitor.philos = philos;
	waiter.monitor = &monitor;
	start_dinner(philos, &monitor, &waiter);
	end_dinner(philos, &monitor);
}
