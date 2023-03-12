/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 00:44:31 by tmuramat          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2023/03/10 00:25:37 by tmuramat         ###   ########.fr       */
=======
/*   Updated: 2023/03/13 02:00:02 by tmuramat         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "ft_deque.h"

<<<<<<< Updated upstream
=======

/**
 * @brief 食事する哲学者問題のシミュレーション
 *
 * @param ac
 * @param av
 * @return int
 */
>>>>>>> Stashed changes
int	main(int ac, char **av)
{
	t_philo_dto	args;
	t_environ	envs;

	if (!(ac == 5 || ac == 6))
		return (put_error());
	if (!input_arguments(av, &args))
		return (put_error());
	envs = init_environs(args);
	simulate_problem(envs);
	return (0);
}
