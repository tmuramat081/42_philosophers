/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:49:45 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/15 05:41:38 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief 哲学者スレッドの初期化
 *
 * @param philos 哲学者の管理情報
 * @param input シミュレーションの入力値
 * @param monitor 監視人の管理情報
 * @param waiter 配膳人の管理情報
 */
void	init_philosophers(t_philosopher *philos, t_philo_dto input)
{
	size_t	i;

	i = 0;
	while (i < (size_t)input.num_of_philos)
	{
		philos[i].id = i;
		philos[i].fork_left = &envs->forks[i];
		philos[i].fork_right = &envs->forks[i + 1 % input.num_of_philos];
		philos[i].count_eaten = 0;
		philos[i].last_eat_at = envs->started_at;
		send_message(&envs->philos[i]);
		pthread_mutex_init(&envs->philos[i].mut, NULL);
		i++;
	}
}

/**
 * @brief モニタースレッドの初期化
 *
 * @param input シミュレーションの入力値
 * @return t_monitor 監視者の管理情報
 */
void	init_monitor(t_monitor *monitor, t_philo_dto input)
{
	monitor->num_of_philos = input.num_of_philos;
	monitor->time_to_die = input.time_to_die;
	monitor->time_to_eat = input.time_to_eat;
	monitor->time_to_sleep = input.time_to_sleep;
	monitor->num_of_eat = input.num_of_eating;
	pthread_mutex_init(&monitor->mut_io, NULL);
}

/**
 * @brief 配膳人用スレッドの初期化
 *
 * @param input
 * @return t_arbitrator
 */
void	init_arbitrator(t_arbitrator *waiter, t_philo_dto input)
{
	waiter->queue = ft_deque_init(sizeof(size_t), input.num_of_philos);
}

/**
 * @brief フォークの初期化
 *
 * @param envs
 * @param input
 */
void	init_forks(pthread_mutex_t *forks, t_philo_dto input)
{
	size_t	i;

	i = 0;
	while (i < (size_t)input.num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_environs(t_environ *envs, t_philo_dto input)
{
	envs->started_at = gettime_ms();
	envs->is_sim_over = false;
	init_forks(envs->forks, input);
	init_arbitrator(&envs->waiter, input);
	init_monitor(&envs->monitor, input);
	init_philosophers(&envs, input);
	envs->monitor->envs = envs;

}
