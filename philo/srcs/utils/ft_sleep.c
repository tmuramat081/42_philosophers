/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:14:42 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/10 00:26:49 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(long time_to_wait)
{
	long	start;

	start = gettime_ms();
	while (true)
	{
		if (get_elapsed_time(start, gettime_ms()) >= time_to_wait)
			break ;
		usleep(100);
	}
}
