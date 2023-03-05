/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 01:48:15 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/05 21:50:22 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	dead_timestamp(char *string, t_philosopher *philo)
{
	long	elapsed_time;

	elapsed_time = get_elapsed_time(philo->started_at, gettime_ms());
	pthread_mutex_lock(&philo->monitor->io);
	printf("%ld %zu %s\n", elapsed_time, philo->id + 1, string);
	pthread_mutex_unlock(&philo->monitor->io);
	return (1);
}

static bool	is_philo_full(t_monitor *monitor, t_philosopher *philos)
{
	size_t	i;
	size_t	cnt_full;

	if (monitor->num_of_eat == -1)
		return (false);
	i = 0;
	cnt_full = 0;
	while (i < monitor->num_of_philos)
	{
		if (philos[i].count_eaten >= (size_t)monitor->num_of_eat)
			cnt_full++;
		i++;
	}
	if (cnt_full >= monitor->num_of_philos)
	{
		monitor->is_sim_over = true;
		return (true);
	}
	return (false);
}

static bool	is_philo_dead(t_monitor *monitor, t_philosopher *philos)
{
	long	elapsed;
	size_t	i;

	i = 0;
	while (i < monitor->num_of_philos)
	{
		elapsed = get_elapsed_time(philos[i].last_eat_at, gettime_ms());
		if (elapsed > (long)monitor->time_to_die)
		{
			monitor->is_sim_over = true;
			dead_timestamp(MSG_DIED, &philos[i]);
			return (true);
		}
		i++;
	}
	return (false);
}

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

