/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkohki <kkohki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:49:45 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/10 23:08:18 by kkohki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief ウェイター用スレッドの初期化
 * 
 * @param input 
 * @return t_arbitrator 
 */
t_arbitrator	init_arbitrator(t_philo_dto input)
{
	t_arbitrator	waiter;

	waiter.queue = ft_deque_init(sizeof(size_t), input.num_of_philos);
	return (waiter);
}

/**
 * @brief モニタースレッドの初期化
 * 
 * @param input シミュレーションの入力値
 * @return t_monitor モニター用構造体
 */
t_monitor	init_monitor(t_philo_dto input)
{
	t_monitor	monitor;
	size_t		i;

	monitor.started_at = gettime_ms();
	monitor.num_of_philos = input.num_of_philos;
	monitor.time_to_die = input.time_to_die;
	monitor.time_to_eat = input.time_to_eat;
	monitor.time_to_sleep = input.time_to_sleep;
	monitor.num_of_eat = input.num_of_eating;
	monitor.is_sim_over = false;
	i = 0;
	while (i < (size_t)input.num_of_philos)
		pthread_mutex_init(&monitor.forks[i++], NULL);
	pthread_mutex_init(&monitor.io, NULL);
	return (monitor);
}

/**
 * @brief 哲学者スレッドの初期化 
 * 
 * @param philos 哲学者用の構造体
 * @param input シミュレーションの入力値
 * @param monitor モニター 
 * @param waiter ウェイター
 */
void	init_philosophers(t_philosopher *philos, t_philo_dto input,
	t_monitor *monitor, t_arbitrator *waiter)
{
	size_t			i;

	i = 0;
	while (i < (size_t)input.num_of_philos)
	{
		philos[i].started_at = gettime_ms();
		philos[i].id = i;
		philos[i].fork_left = &monitor->forks[i];
		philos[i].fork_right = \
			&monitor->forks[i + 1 % input.num_of_philos];
		philos[i].count_eaten = 0;
		philos[i].last_eat_at = philos[i].started_at;
		philos[i].monitor = monitor;
		philos[i].waiter = waiter;
		pthread_mutex_init(&philos[i].mutex, NULL);
		send_message(&philos[i]);
		i++;
	}
}
