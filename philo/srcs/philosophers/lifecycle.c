/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:49:27 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/21 14:04:15 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief 哲学者の行動ルーチン
 *
 * @param p_philo 哲学者への参照アドレス
 * @return void*
 */
void	*lifecycle(void *p_philo)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)p_philo;
	while (true)
	{
		if (!do_think(philo))
			break ;
		if (!do_eat(philo, philo->monitor))
			break ;
		if (!do_sleep(philo, philo->monitor))
			break ;
	}
	return (NULL);
}
