/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:49:27 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/03 22:49:28 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*lifecycle(void *p_philo)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)p_philo;
	send_message(philo);
	while (true)
	{
		if (!do_think(philo)
			|| !do_eat(philo, philo->monitor)
			|| !do_sleep(philo, philo->monitor))
			break ;
	}
	return (NULL);
}
