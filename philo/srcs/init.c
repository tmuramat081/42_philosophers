/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:49:45 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/21 21:35:20 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief 配膳人スレッドの初期化
 *
 * @param args
 * @return t_arbitrator
 */
void	init_arbitrator(t_arbitrator *waiter, t_philo_dto args)
{
	waiter->queue = ft_deque_init(sizeof(size_t), args.num_of_philos);
}

/**
 * @brief 監視者スレッドの初期化
 *
 * @param args シミュレーションの入力値
 * @return t_monitor 監視者の管理情報
 */
void	init_monitor(t_monitor *monitor, t_philo_dto args)
{
	size_t		i;

	monitor->started_at = args.started_at;
	monitor->num_of_philos = args.num_of_philos;
	monitor->time_to_die = args.time_to_die;
	monitor->time_to_eat = args.time_to_eat;
	monitor->time_to_sleep = args.time_to_sleep;
	monitor->num_of_eat = args.num_of_eating;
	monitor->is_sim_over = false;
	i = 0;
	while (i < (size_t)args.num_of_philos)
		pthread_mutex_init(&monitor->forks[i++], NULL);
	pthread_mutex_init(&monitor->mutex_write, NULL);
	pthread_mutex_init(&monitor->mutex_check, NULL);
}

/**
 * @brief 哲学者スレッドの初期化
 *
 * @param philos 哲学者の管理情報
 * @param args シミュレーションの入力値
 * @param monitor 監視者の管理情報
 * @param waiter 配膳人の管理情報
 */
void	init_philosophers(t_philosopher *philos, t_philo_dto args,
	t_monitor *monitor, t_arbitrator *waiter)
{
	size_t			i;

	i = 0;
	while (i < (size_t)args.num_of_philos)
	{
		philos[i].started_at = args.started_at;
		philos[i].id = i;
		philos[i].fork_left = &monitor->forks[i];
		philos[i].fork_right = &monitor->forks[(i + 1) % args.num_of_philos];
		philos[i].count_eaten = 0;
		philos[i].last_eat_at = philos[i].started_at;
		philos[i].monitor = monitor;
		philos[i].waiter = waiter;
		pthread_mutex_init(&philos[i].mutex, NULL);
		i++;
	}
}
