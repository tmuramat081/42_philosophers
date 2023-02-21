/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkohki <kkohki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 00:36:29 by tmuramat          #+#    #+#             */
/*   Updated: 2023/02/20 16:00:28 by kkohki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_dinner(t_philosopher *philos, t_arbitrator *waiter)
{
	size_t		i;
	pthread_t	ptd;

	pthread_create(&ptd, NULL, monitor, waiter);
	i = 0;
	while (i < waiter->num_of_philos)
	{
		pthread_create(&ptd, NULL, lifecycle, &philos[i]);
		pthread_detach(ptd);
		i++;
	}
}

void	simulate_problem(t_philo_dto input)
{
	t_arbitrator	*waiter;
	t_philosopher	*philos;

	waiter = init_waiter(input);
	philos = init_philosophers(input, waiter);
	waiter->philos = philos;
	start_dinner(philos, waiter);
}
