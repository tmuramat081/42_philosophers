/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque_mutex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 00:44:29 by tmuramat          #+#    #+#             */
/*   Updated: 2023/02/22 00:50:23 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_deque.h"

void	ft_deque_lock(t_deque *deque)
{
	pthread_mutex_lock(&deque->mutex);
}

void	ft_deque_unlock(t_deque	*deque)
{
	pthread_mutex_unlock(&deque->mutex);
}
