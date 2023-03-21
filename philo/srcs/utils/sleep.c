/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:14:42 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/21 23:31:53 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	usleep_ms(t_philosopher *philo, long time_to_wait)
{
	long	start;

	start = philo->action_at;
	usleep(time_to_wait * 900);
	while (true)
	{
		if (get_elapsed_time(start, gettime_ms()) >= time_to_wait)
			break ;
		usleep(100);
	}
}
