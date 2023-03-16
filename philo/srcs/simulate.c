/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 00:36:29 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/17 02:04:18 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief 作成したスレッドのリソースを解放する
 *
 * @param philos 哲学者
 * @param monitor 監視者
 */
void	destroy_threads(t_environ *envs)
{
	size_t	i;

	i = 0;
	while (i < envs->monitor.num_of_philos)
	{
		pthread_join(envs->philos[i].thread_id, NULL);
		pthread_mutex_destroy(&envs->philos[i].mut);
		pthread_mutex_destroy(&envs->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&envs->monitor.mut_io);
	ft_deque_delete(&envs->waiter.queue);
}

/**
 * @brief スレッドを新規作成する
 *
 * @param philos 哲学者
 * @param monitor 監視者
 * @param waiter 配膳人
 */
void	create_threads(t_environ *envs)
{
	size_t	i;

	pthread_create(&envs->waiter.thread_id, NULL, server, &envs->waiter);
	pthread_detach(envs->waiter.thread_id);
	pthread_create(&envs->monitor.thread_id, NULL, checker, &envs->monitor);
	pthread_detach(envs->monitor.thread_id);
	i = 0;
	while (i < envs->monitor.num_of_philos)
	{
		pthread_create(&envs->philos[i].thread_id, NULL, lifecycle,
			&envs->philos[i]);
		i++;
	}
}

/**
 * @brief シミュレーションの開始
 *
 */
void	simulate_problem(t_philo_dto args)
{
	t_environ	envs;

	envs = init_environs(args);
	create_threads(&envs);
	destroy_threads(&envs);
}
