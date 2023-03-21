/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:14:53 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/21 19:43:05 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

int	dead_timestamp(t_philosopher *philo, t_monitor *monitor, long now)
{
	long	elapsed_time;

	pthread_mutex_lock(&monitor->mutex_write);
	elapsed_time = get_elapsed_time(philo->started_at, now);
	printf("%ld %zu %s\n", elapsed_time, philo->id + 1, MSG_DIED);
	pthread_mutex_unlock(&monitor->mutex_write);
	pthread_mutex_lock(&philo->monitor->mutex_check);
	monitor->is_sim_over = true;
	pthread_mutex_unlock(&philo->monitor->mutex_check);
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
	long	now;
	size_t	i;

	i = 0;
	while (i < monitor->num_of_philos)
	{
		pthread_mutex_lock(&philos[i].mutex);
		now = gettime_ms();
		if (get_elapsed_time(philos[i].last_eat_at, now) > monitor->time_to_die)
		{
			dead_timestamp(&philos[i], monitor, now);
			pthread_mutex_unlock(&philos[i].mutex);
			return (true);
		}
		pthread_mutex_unlock(&philos[i].mutex);
		i++;
	}
	return (false);
}
