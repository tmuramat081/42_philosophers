/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:14:53 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/15 23:50:39 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	dead_timestamp(char *string, t_philosopher *philo)
{
	long	elapsed_time;
	long	now;

	now = gettime_ms();
	elapsed_time = get_elapsed_time(philo->started_at, now);
	pthread_mutex_lock(&philo->monitor->mut_io);
	printf("%ld %zu %s\n", elapsed_time, philo->id + 1, string);
	pthread_mutex_unlock(&philo->monitor->mut_io);
	return (1);
}

bool	is_philo_dead(t_monitor *monitor, t_philosopher *philos)
{
	long	elapsed;
	size_t	i;

	i = 0;
	while (i < monitor->num_of_philos)
	{
		pthread_mutex_lock(&philos[i].mut);
		elapsed = get_elapsed_time(philos[i].last_eat_at, gettime_ms());
		if (elapsed > (long)monitor->time_to_die)
		{
			monitor->is_sim_over = true;
			dead_timestamp(MSG_DIED, &philos[i]);
			pthread_mutex_unlock(&philos[i].mut);
			return (true);
		}
		pthread_mutex_unlock(&philos[i].mut);
		i++;
	}
	return (false);
}
