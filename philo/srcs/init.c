/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 00:16:13 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/02 01:24:00 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philosopher	*init_philosophers(t_philos_dto philos_dto)
{
	t_philosopher	*philos;
	size_t			i;

	philos = malloc(sizeof(t_philosopher) * philos_dto.num_of_philos);
	i = 0;
	while (i < philos_dto.num_of_philos)
	{
		pthread_create(&philos[i].thread_id, NULL, lifecycle, &philos[i]);
		philos[i].id = i;
		philos[i].is_dead = false;
		i++;
	}
	return (philos);
}

t_arbitrator	*init_waiter(t_philos_dto philos_dto)
{
	t_arbitrator	*waiter;

	waiter = malloc(sizeof(t_arbitrator));
	waiter->num_of_philos = philos_dto.num_of_philos;
	waiter->time_to_die = philos_dto.time_to_die;
	waiter->time_to_eat = philos_dto.time_to_eat;
	waiter->time_to_sleep = philos_dto.time_to_sleep;
	waiter->num_of_eating = philos_dto.num_of_eating;
	return (waiter);
}
