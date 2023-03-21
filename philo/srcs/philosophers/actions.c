/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:49:27 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/21 16:03:08 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

/**
 * @brief 哲学者：フォークを取る
 *
 * @param philo 哲学者
 * @return int
 */
static int	do_pick_up_forks(t_philosopher *philo)
{
	pthread_mutex_lock(philo->fork_left);
	if (!put_timestamp(MSG_TAKEN_FORK, philo))
		return (0);
	pthread_mutex_lock(philo->fork_right);
	if (!put_timestamp(MSG_TAKEN_FORK, philo))
		return (0);
	return (1);
}

/**
 * @brief 哲学者：フォークを置く
 *
 * @param philo 哲学者の管理情報
 * @return int
 */
static int	do_take_down_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (0);
}

/**
 * @brief 哲学者：食事
 *
 * @param philo 哲学者
 * @param monitor　監視者
 * @return int　正常に食事を行なった場合は1, 動作の前に死を迎えた場合は0を返す。
 */
int	do_eat(t_philosopher *philo, t_monitor *monitor)
{
	if (!receive_message(philo))
		return (0);
	if (!do_pick_up_forks(philo))
		return (0);
	pthread_mutex_lock(&philo->mutex);
	philo->last_eat_at = gettime_ms();
	pthread_mutex_unlock(&philo->mutex);
	if (!put_timestamp(MSG_EATING, philo))
		return (0);
	usleep_ms(philo, monitor->time_to_eat);
	do_take_down_forks(philo);
	philo->count_eaten++;
	send_message(philo);
	return (1);
}

/**
 * @brief 哲学者：睡眠
 *
 * @param philo 哲学者
 * @param monitor モニター
 * @return int
 */
int	do_sleep(t_philosopher *philo, t_monitor *monitor)
{
	if (!put_timestamp(MSG_SLEEPING, philo))
		return (0);
	usleep_ms(philo, monitor->time_to_sleep);
	return (1);
}

/**
 * @brief 哲学者：思考
 *
 * @param philo 哲学者
 * @return int
 */
int	do_think(t_philosopher *philo)
{
	if (!put_timestamp(MSG_THINKING, philo))
		return (0);
	return (1);
}
