/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 00:36:29 by tmuramat          #+#    #+#             */
/*   Updated: 2023/02/24 00:54:57 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor(void *p_waiter)
{
	t_philosopher	*philos;
	t_arbitrator	*waiter;
	long			elapsed;
	size_t			i;

	waiter = (t_arbitrator *)p_waiter;
	philos = waiter->philos;
	while (true)
	{
		i = 0;
		while (i < waiter->num_of_philos)
		{
			elapsed = get_elapsed_time(philos[i].last_eat_at, gettime_ms());
			if (elapsed > (long)waiter->time_to_eat)
			{
				pthread_mutex_unlock(&waiter->is_end);
				put_timestamp(MSG_DIED, &philos[i]);
				return (NULL);
			}
			i++;
		}
	}
}

void	start_dinner(t_philosopher *philos, t_arbitrator *waiter)
{
	size_t		i;

	pthread_create(&waiter->thread_id, NULL, monitor, waiter);
//	pthread_detach(waiter->thread_id);
	i = 0;
	while (i < waiter->num_of_philos)
	{
		pthread_create(&philos[i].thread_id, NULL, lifecycle, &philos[i]);
//		pthread_detach(philos[i].thread_id);
		i++;
	}
}

void	end_dinner(t_philosopher *philos, t_arbitrator *waiter)
{
	size_t	i;

	pthread_join(waiter->thread_id, NULL);
	pthread_mutex_destroy(&waiter->is_end);
	i = 0;
	while (i < waiter->num_of_philos)
	{
		pthread_join(philos[i].thread_id, NULL);
		pthread_mutex_destroy(&philos[i].mutex);
		pthread_mutex_destroy(&waiter->forks[i]);
		i++;
	}
	free(philos);
}

void	simulate_problem(t_philo_dto input)
{
	t_arbitrator	waiter;
	t_philosopher	*philos;

	waiter = init_waiter(input);
	philos = init_philosophers(input, &waiter);
	waiter.philos = philos;
	start_dinner(philos, &waiter);
	pthread_mutex_lock(&waiter.is_end);
	pthread_mutex_unlock(&waiter.is_end);
	end_dinner(philos, &waiter);
}
