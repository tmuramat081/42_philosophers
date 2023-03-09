/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 01:48:15 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/10 01:41:13 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	dead_timestamp(char *string, t_philosopher *philo)
{
	long	elapsed_time;
	long	now;

	now = gettime_ms();
	elapsed_time = get_elapsed_time(philo->started_at, now);
	pthread_mutex_lock(&philo->monitor->io);
	printf("%ld %zu %s\n", elapsed_time, philo->id + 1, string);
	pthread_mutex_unlock(&philo->monitor->io);
	return (1);
}

/**
 * @brief 哲学者の状態監視
 *
 * @param p_monitor モニターへの参照アドレス
 * @return void*
 */
void	*checker(void *p_monitor)
{
	t_philosopher	*philos;
	t_monitor		*monitor;

	monitor = (t_monitor *)p_monitor;
	philos = monitor->philos;
	while (true)
	{
		if (is_philo_dead(monitor, philos)
			|| is_philo_full(monitor, philos))
			break ;
	}
	return (NULL);
}
