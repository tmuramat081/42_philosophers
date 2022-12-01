/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 00:36:29 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/02 01:27:52 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	do_eat(t_philosopher *philo)
{
	(void)philo;
	printf("eating\n");
}

void	do_sleep(t_philosopher *philo)
{
	(void)philo;
	printf("sleeping\n");
}

void	*lifecycle(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	while (true)
	{
		do_eat(philo);
		do_sleep(philo);
	}
}

void	solve_philos_problem(t_philos_dto philos_dto)
{
	t_arbitrator	*waiter;
	t_philosopher	*philos;

	waiter = init_waiter(philos_dto);
	philos = init_philosophers(philos_dto);
}
