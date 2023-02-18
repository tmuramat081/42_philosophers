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

long	get_elapsed_time_usec(long start_ms)
{
	t_timeval	now;
	long		now_ms;

	if (gettimeofday(&now, NULL) < 0)
		exit(1);
	now_ms = (long)(now.tv_sec * 1000) + (long)(now.tv_usec / 1000);
	return (now_ms - start_ms);
}

void	put_timestump(char *string, t_philosopher *philo)
{
	long	elapsed_time;

	elapsed_time = get_elapsed_time_usec(philo->start_time);
	printf("%ld %zu %s\n", elapsed_time, philo->id, string);
}

void	do_think(t_philosopher *philo)
{
	sleep(philo->time_to_sleep);
	put_timestump(MSG_EATING, philo);
}

void	do_sleep(t_philosopher *philo)
{
	sleep(philo->time_to_sleep);
	put_timestump(MSG_SLEEPING, philo);
}

void	do_eat(t_philosopher *philo)
{
	sleep(philo->time_to_eat);
	put_timestump(MSG_EATING, philo);
}

void	*lifecycle(void *void_philo)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)void_philo;
	while (true)
	{
		do_eat(philo);
		do_sleep(philo);
		do_think(philo);
	}
}
