/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:50:12 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/03 23:51:50 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "ft_deque.h"

bool	wait_ms(t_arbitrator *waiter)
{
	if (waiter->monitor->is_sim_over == true)
		return (false);
	return (true);
}

void	*server(void	*p_waiter)
{
	t_arbitrator	*waiter;

	waiter = p_waiter;
	while (wait_ms(waiter))
	{
		;
	//	printf("size=%zu\n", ft_deque_size(waiter->queue));
	}
	return (NULL);
}

void	send_message(t_philosopher *philo)
{
	t_arbitrator	*waiter;

	waiter = philo->waiter;
	ft_deque_lock(waiter->queue);
	ft_deque_push_back(waiter->queue, &philo->id);
	ft_deque_unlock(waiter->queue);
}

void	receive_message(t_philosopher *philo)
{
	t_arbitrator	*waiter;
	size_t			*top;

	waiter = philo->waiter;
	while (wait_ms(waiter))
	{
		ft_deque_lock(waiter->queue);
		top = NULL;
		top = ft_deque_front(waiter->queue);
		if (top && *top == philo->id)
		{
			printf("%zu\n", *top);
			ft_deque_pop_front(waiter->queue, top);
			ft_deque_unlock(waiter->queue);
			break ;
		}
		ft_deque_unlock(waiter->queue);
	}
}
