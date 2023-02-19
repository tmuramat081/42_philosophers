/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 11:33:36 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/04 12:06:26 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
# include <pthread.h>

void	do_eat(t_philosopher *philo, t_arbitrator *waiter)
{
	(void)waiter;
	pthread_mutex_unlock(philo->mutex);
	put_timestamp(MSG_EATING, philo);
	philo->time_last_eaten = gettime_ms();
	philo->count_eaten++;
	pthread_mutex_lock(philo->mutex);
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

void	*lifecycle(void *p_philo)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)p_philo;
	while (true)
	{
		do_pick_up_forks(philo);
		do_eat(philo, philo->waiter);
		do_take_down_forks(philo);
		usleep(philo->waiter->time_to_eat * 1000);
		put_timestamp(MSG_EATING, philo);
	}
}
