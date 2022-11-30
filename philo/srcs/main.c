/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 00:44:31 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/01 01:51:32 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	handle_error(void)
{
	exit(EXIT_FAILURE);
}

t_waiter	input_arguments(char **av)
{
	t_waiter	waiter;

	waiter.num_of_philosophers = atoi(av[1]);
	waiter.time_to_die = atoi(av[2]);
	waiter.time_to_eat = atoi(av[3]);
	waiter.time_to_sleep = atoi(av[4]);
	if (av[5])
	{
		waiter.num_of_eating = atoi(av[5]);
	}
	return (waiter);
}

int	main(int ac, char **av)
{
	t_waiter	waiter;

	if (!(ac == 4 || ac == 5))
		handle_error();
	waiter = input_arguments(av);
	solve_philosophers_problem(waiter);
	return (0);
}
