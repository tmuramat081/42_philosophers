/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:14:42 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/21 15:02:57 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	usleep_ms(long time_to_wait)
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
