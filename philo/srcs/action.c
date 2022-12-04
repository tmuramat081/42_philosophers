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

void	put_timestump(char *str)
{
	
}

void	*lifecycle(void *void_philo)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)void_philo;
	while (true)
	{
		printf("eat");
		printf("sleep");
	}
}
