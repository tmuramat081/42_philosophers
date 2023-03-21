/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 00:36:29 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/21 19:59:10 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Create a threads object
 *
 * @param philos スレッドを新規作成する
 * @param monitor モニター
 * @param waiter ウェイター
 */
void	create_threads(
	t_philosopher *philos, t_monitor *monitor, t_arbitrator *waiter)
{
	size_t		i;

	pthread_create(&waiter->thread_id, NULL, server, waiter);
	pthread_create(&monitor->thread_id, NULL, checker, monitor);
	i = 0;
	while (i < monitor->num_of_philos)
	{
		pthread_create(&philos[i].thread_id, NULL, lifecycle, &philos[i]);
		usleep(50);
		i++;
	}
}

/**
 * @brief 作成したスレッドのリソースを解放する
 *
 * @param philos 哲学者
 * @param monitor モニター
 */
void	destroy_threads(
	t_philosopher *philos, t_monitor *monitor, t_arbitrator *waiter)
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
	pthread_join(monitor->thread_id, NULL);
	pthread_join(waiter->thread_id, NULL);
	pthread_mutex_destroy(&monitor->mutex_check);
	pthread_mutex_destroy(&monitor->mutex_write);
	ft_deque_delete(&waiter->queue);
}

void	send_first_message(t_philosopher *philos, t_philo_dto args)
{
	size_t	i;

	i = 0;
	while (i < (size_t)args.num_of_philos)
	{
		send_message(&philos[i]);
		i++;
	}
}

/**
 * @brief シミュレーションの開始
 *
 */
void	simulate_problem(t_philo_dto args)
{
	t_monitor		monitor;
	t_arbitrator	waiter;
	t_philosopher	philos[PHILO_MAX];

	init_arbitrator(&waiter, args);
	init_monitor(&monitor, args);
	init_philosophers(philos, args, &monitor, &waiter);
	monitor.philos = philos;
	waiter.monitor = &monitor;
	send_first_message(philos, args);
	create_threads(philos, &monitor, &waiter);
	destroy_threads(philos, &monitor, &waiter);
}
