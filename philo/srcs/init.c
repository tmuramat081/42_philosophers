/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:49:45 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/13 02:16:39 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief フォークの初期化
 *
 * @param envs
 * @param input
 */
void	init_forks(t_environ *envs, t_philo_dto input)
{
	size_t	i;

	i = 0;
	while (i < (size_t)input.num_of_philos)
	{
		pthread_mutex_init(&envs->forks[i], NULL);
		i++;
	}
}

/**
 * @brief ウェイター用スレッドの初期化
 *
 * @param input
 * @return t_arbitrator
 */
void	init_arbitrator(t_environ *envs, t_philo_dto input)
{
	envs->waiter.queue = ft_deque_init(sizeof(size_t), input.num_of_philos);
}

/**
 * @brief モニタースレッドの初期化
 *
 * @param input シミュレーションの入力値
 * @return t_monitor モニター用構造体
 */
void	init_monitor(t_environ *envs, t_philo_dto input)
{
	envs->monitor.started_at = envs->started_at;
	envs->monitor.num_of_philos = input.num_of_philos;
	envs->monitor.time_to_die = input.time_to_die;
	envs->monitor.time_to_eat = input.time_to_eat;
	envs->monitor.time_to_sleep = input.time_to_sleep;
	envs->monitor.num_of_eat = input.num_of_eating;
	envs->monitor.is_sim_over = false;
	pthread_mutex_init(&envs->monitor.mut_io, NULL);
}

/**
 * @brief 哲学者スレッドの初期化
 *
 * @param philos 哲学者用の構造体
 * @param input シミュレーションの入力値
 * @param monitor モニター
 * @param waiter ウェイター
 */
void	init_philosophers(t_environ *envs, t_philo_dto input)
{
	size_t	i;

	i = 0;
	while (i < (size_t)input.num_of_philos)
	{
		envs->philos[i].started_at = envs->started_at;
		envs->philos[i].id = i;
		envs->philos[i].fork_left = &envs->forks[i];
		envs->philos[i].fork_right = &envs->forks[i + 1 % input.num_of_philos];
		envs->philos[i].count_eaten = 0;
		envs->philos[i].last_eat_at = envs->started_at;
		pthread_mutex_init(&envs->philos[i].mutex, NULL);
		send_message(&envs->philos[i]);
		i++;
	}
}

t_environ	init_environs(t_philo_dto input)
{
	t_environ	envs;

	envs.started_at = gettime_ms();
	init_forks(&envs, input);
	init_arbitrator(&envs, input);
	init_monitor(&envs, input);
	init_philosophers(&envs, input);
	return (envs);
}
