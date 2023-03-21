/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_full.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:14:51 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/21 21:41:13 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief 哲学者の満腹判定
 *
 * @param monitor 監視者への参照アドレス
 * @param philos　哲学者への参照アドレス
 * @return true すべての哲学者が必要な食事回数に達した
 * @return false　すべての哲学者が必要な食事回数に達していない
 */
bool	is_philo_full(t_monitor *monitor, t_philosopher *philos)
{
	size_t	i;

	if (monitor->num_of_eat == -1)
		return (false);
	i = 0;
	while (i < monitor->num_of_philos)
	{
		pthread_mutex_lock(&philos[i].mutex);
		if (philos[i].count_eaten < (size_t)monitor->num_of_eat)
		{
			pthread_mutex_unlock(&philos[i].mutex);
			return (false);
		}
		pthread_mutex_unlock(&philos[i].mutex);
		i++;
	}
	pthread_mutex_lock(&monitor->mutex_check);
	monitor->is_sim_over = true;
	pthread_mutex_unlock(&monitor->mutex_check);
	return (true);
}
