/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 00:44:31 by tmuramat          #+#    #+#             */
/*   Updated: 2023/03/21 12:51:37 by tmuramat         ###   ########.fr       */
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

	if (!(ac == 5 || ac == 6))
		return (put_error());
	if (!input_arguments(av, &args))
		return (put_error());
	simulate_problem(args);
	return (0);
}
