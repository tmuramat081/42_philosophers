/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:50:12 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/21 20:33:53 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "ft_deque.h"

/**
 * @brief シミュレーションの終了判定
 *
 * @param waiter
 * @return true シミュレーション終了
 * @return false シミュレーション継続
 */
static bool	_is_over(t_arbitrator *waiter)
{
	pthread_mutex_lock(&waiter->monitor->mutex_check);
	if (waiter->monitor->is_sim_over == true)
	{
		pthread_mutex_unlock(&waiter->monitor->mutex_check);
		return (false);
	}
	pthread_mutex_unlock(&waiter->monitor->mutex_check);
	return (true);
}

/**
 * @brief 食事許可キューの待機
 *
 * @param p_waiter ウェイターへの参照アドレス
 * @return void*
 */
void	*server(void	*p_waiter)
{
	t_arbitrator	*waiter;

	waiter = p_waiter;
	while (_is_over(waiter))
		;
	puts("waiter END");
	return (NULL);
}
