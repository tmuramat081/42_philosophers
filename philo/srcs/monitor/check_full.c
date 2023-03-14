/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_full.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:14:51 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/14 23:48:59 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_philo_full(t_monitor *monitor, t_philosopher *philos)
{
	size_t	i;
	size_t	cnt_full;

	if (monitor->num_of_eat == -1)
		return (false);
	i = 0;
	cnt_full = 0;
	while (i < monitor->num_of_philos)
	{
		pthread_mutex_lock(&philos[i].mut);
		if (philos[i].count_eaten >= (size_t)monitor->num_of_eat)
			cnt_full++;
		pthread_mutex_unlock(&philos[i].mut);
		i++;
	}
	if (cnt_full >= monitor->num_of_philos)
	{
		pthread_mutex_lock(&philos[i].mut);
		monitor->envs->is_sim_over = true;
		pthread_mutex_unlock(&philos[i].mut);
		return (true);
	}
	return (false);
}
