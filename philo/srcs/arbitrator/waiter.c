/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:50:12 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/14 23:48:36 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "ft_deque.h"

static bool	_is_over(t_arbitrator *waiter)
{
	if (waiter->envs->is_sim_over == true)
		return (false);
	return (true);
}

void	*server(void	*p_waiter)
{
	t_arbitrator	*waiter;

	waiter = p_waiter;
	while (_is_over(waiter))
		;
	return (NULL);
}
