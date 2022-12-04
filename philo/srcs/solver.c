/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 00:36:29 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/04 11:54:31 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_dinner(t_philosopher *philos, t_arbitrator *waiter)
{
	size_t	i;

	i = 0;
	while (i < waiter->num_of_philos)
	{
		pthread_create(&philos[i].thread_id, NULL, lifecycle, &philos[i]);
		i++;
	}
}

void	end_dinner(t_philosopher *philos, t_arbitrator *waiter)
{
	size_t	i;

	i = 0;
	while (i < waiter->num_of_philos)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}

}

void	solve_philos_problem(t_dto dto)
{
	t_arbitrator	*waiter;
	t_philosopher	*philos;

	philos = init_philosophers(dto);
	waiter = init_waiter(dto);
	start_dinner(philos, waiter);
	end_dinner(philos, waiter);
}