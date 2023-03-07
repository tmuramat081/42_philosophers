/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:14:58 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/07 23:15:01 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	_is_over(t_arbitrator *waiter)
{
	if (waiter->monitor->is_sim_over == true)
		return (false);
	return (true);
}

void	send_message(t_philosopher *philo)
{
	t_arbitrator	*waiter;

	waiter = philo->waiter;
	ft_deque_lock(waiter->queue);
	ft_deque_push_back(waiter->queue, &philo->id);
	ft_deque_unlock(waiter->queue);
}

int	receive_message(t_philosopher *philo)
{
	t_arbitrator	*waiter;
	size_t			*top;

	waiter = philo->waiter;
	while (true)
	{
		if (!_is_over(waiter))
			return (0);
		if (ft_deque_size(waiter->queue) <= 1)
			continue ;
		top = ft_deque_front(waiter->queue);
		if (top && *top == philo->id)
		{
			ft_deque_pop_front(waiter->queue, top);
			ft_deque_unlock(waiter->queue);
			break ;
		}
		ft_deque_unlock(waiter->queue);
	}
	return (1);
}
