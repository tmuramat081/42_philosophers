/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:49:27 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/03 22:49:28 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"
#include <pthread.h>

static int	do_pick_up_forks(t_philosopher *philo)
{
	pthread_mutex_lock(philo->fork_left);
	if (!put_timestamp(MSG_TAKEN_FORK, philo))
		return (0);
	pthread_mutex_lock(philo->fork_right);
	if (!put_timestamp(MSG_TAKEN_FORK, philo))
		return (0);
	return (1);
}

static int	do_take_down_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (0);
}

int	do_eat(t_philosopher *philo, t_monitor *monitor)
{
	receive_message(philo);
	do_pick_up_forks(philo);
	philo->last_eat_at = gettime_ms();
	if (!put_timestamp(MSG_EATING, philo))
		return (0);
	usleep(monitor->time_to_eat * 1000);
	do_take_down_forks(philo);
	philo->count_eaten++;
	send_message(philo);
	return (1);
}

int	do_sleep(t_philosopher *philo, t_monitor *monitor)
{
	if (!put_timestamp(MSG_SLEEPING, philo))
		return (0);
	usleep(monitor->time_to_sleep * 1000);
	return (1);
}

int	do_think(t_philosopher *philo)
{
	if (!put_timestamp(MSG_THINKING, philo))
		return (0);
	return (1);
}