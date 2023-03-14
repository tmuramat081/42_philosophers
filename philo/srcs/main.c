/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 00:44:31 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/15 05:20:25 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "ft_deque.h"

/**
 * @brief 食事する哲学者問題のシミュレーション
 *
 * @param ac
 * @param av
 * @return int
 */
int	main(int ac, char **av)
{
	t_philo_dto	args;
	t_environ	envs;

	if (!(ac == 5 || ac == 6))
		return (put_error());
	if (!input_arguments(av, &args))
		return (put_error());
	init_environs(&envs, args);
	simulate_problem(&envs);
	return (0);
}
