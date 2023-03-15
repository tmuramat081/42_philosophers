/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 00:36:29 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/16 00:01:07 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief 作成したスレッドのリソースを解放する
 *
 * @param philos 哲学者
 * @param monitor モニター
 */
void	destroy_threads(t_environ *envs)
{
	t_arbitrator		*waiter;
	t_monitor			*monitor;
	t_philosopher		*philos;
	size_t				i;

	waiter = &envs->waiter;
	monitor = &envs->monitor;
	philos = envs->philos;
	i = 0;
	while (i < monitor->num_of_philos)
	{
		pthread_join(philos[i].thread_id, NULL);
		pthread_mutex_destroy(&philos[i].mut);
		pthread_mutex_destroy(&envs->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&monitor->mut_io);
	ft_deque_delete(&waiter->queue);
}

/**
 * @brief Create a threads object
 *
 * @param philos スレッドを新規作成する
 * @param monitor モニター
 * @param waiter 配膳人
 */
void	create_threads(t_environ *envs)
{
	t_arbitrator		*waiter;
	t_monitor			*monitor;
	t_philosopher		*philos;
	size_t				i;

	waiter = &envs->waiter;
	monitor = &envs->monitor;
	philos = envs->philos;
	pthread_create(&waiter->thread_id, NULL, server, waiter);
	pthread_detach(waiter->thread_id);
	pthread_create(&monitor->thread_id, NULL, checker, monitor);
	pthread_detach(monitor->thread_id);
	i = 0;
	while (i < monitor->num_of_philos)
	{
		pthread_create(&philos[i].thread_id, NULL, lifecycle, &philos[i]);
		i++;
	}
}

/**
 * @brief シミュレーションの開始
 *
 */
void	simulate_problem(t_environ *envs)
{
	create_threads(envs);
	destroy_threads(envs);
}
