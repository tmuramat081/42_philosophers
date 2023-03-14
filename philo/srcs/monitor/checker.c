/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 01:48:15 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/14 23:14:03 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*checker(void *p_monitor)
{
	t_philosopher	*philos;
	t_monitor		*monitor;

	monitor = (t_monitor *)p_monitor;
	philos = monitor->envs->philos;
	while (true)
	{
		if (is_philo_dead(monitor, philos)
			|| is_philo_full(monitor, philos))
			break ;
	}
	return (NULL);
}
