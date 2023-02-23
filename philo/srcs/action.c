/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 11:33:36 by tmuramat          #+#    #+#             */
/*   Updated: 2023/02/24 00:44:58 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

void	do_eat(t_philosopher *philo, t_arbitrator *waiter)
{
	pthread_mutex_lock(&philo->mutex);
	philo->last_eat_at = gettime_ms();
	put_timestamp(MSG_EATING, philo);
	usleep(waiter->time_to_eat * 1000);
	philo->count_eaten++;
	pthread_mutex_unlock(&philo->mutex);
}

void	do_pick_up_forks(t_philosopher *philo)
{
	pthread_mutex_lock(philo->fork_left);
	put_timestamp(MSG_TAKEN_FORK, philo);
	pthread_mutex_lock(philo->fork_right);
	put_timestamp(MSG_TAKEN_FORK, philo);
}

void	do_take_down_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void	do_sleep(t_philosopher *philo, t_arbitrator *waiter)
{
	put_timestamp(MSG_SLEEPING, philo);
	usleep(waiter->time_to_sleep * 1000);
}

void	do_think(t_philosopher *philo)
{
	put_timestamp(MSG_THINKING, philo);
}

void	*lifecycle(void *p_philo)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)p_philo;
	if (philo->id % 2)
		usleep(15000);
	while (true)
	{
		do_pick_up_forks(philo);
		do_eat(philo, philo->waiter);
		do_take_down_forks(philo);
		do_sleep(philo, philo->waiter);
		do_think(philo);
	}
}
