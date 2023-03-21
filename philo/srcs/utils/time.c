/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:49:04 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/21 18:49:24 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	gettime_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)(tv.tv_sec * 1000) + (long)(tv.tv_usec / 1000));
}

long	get_elapsed_time(long start_ms, long end_ms)
{
	return (end_ms - start_ms);
}

int	put_timestamp(char *string, t_philosopher *philo)
{
	long	elapsed_time;

	pthread_mutex_lock(&philo->monitor->mutex_check);
	philo->action_at = gettime_ms();
	elapsed_time = get_elapsed_time(philo->started_at, philo->action_at);
	if (philo->monitor->is_sim_over == true)
	{
		pthread_mutex_unlock(&philo->monitor->mutex_check);
		return (0);
	}
	pthread_mutex_unlock(&philo->monitor->mutex_check);
	pthread_mutex_lock(&philo->monitor->mutex_write);
	printf("%ld %zu %s\n", elapsed_time, philo->id + 1, string);
	pthread_mutex_unlock(&philo->monitor->mutex_write);
	return (1);
}
