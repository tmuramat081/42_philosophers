/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:14:53 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/21 13:17:23 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	dead_timestamp(char *string, t_philosopher *philo)
{
	long	elapsed_time;

	elapsed_time = get_elapsed_time(philo->started_at, gettime_ms());
	pthread_mutex_lock(&philo->monitor->mutex_io);
	printf("%ld %zu %s\n", elapsed_time, philo->id + 1, string);
	pthread_mutex_unlock(&philo->monitor->mutex_io);
	return (1);
}

/**
 * @brief 哲学者の死亡判定
 *
 * @param monitor モニターへの参照アドレス
 * @param philos 哲学者への参照アドレス
 * @return true　いずれかの哲学者が死を迎えた
 * @return false　いずれの哲学者も死を迎えていない
 */
bool	is_philo_dead(t_monitor *monitor, t_philosopher *philos)
{
	long	elapsed;
	size_t	i;

	i = 0;
	while (i < monitor->num_of_philos)
	{
		pthread_mutex_lock(&philos[i].mutex);
		elapsed = get_elapsed_time(philos[i].last_eat_at, gettime_ms());
		if (elapsed > (long)monitor->time_to_die)
		{
			monitor->is_sim_over = true;
			dead_timestamp(MSG_DIED, &philos[i]);
			pthread_mutex_unlock(&philos[i].mutex);
			return (true);
		}
		pthread_mutex_unlock(&philos[i].mutex);
		i++;
	}
	return (false);
}
