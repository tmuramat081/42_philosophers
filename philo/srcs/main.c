/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 00:44:31 by tmuramat          #+#    #+#             */
/*   Updated: 2023/02/23 19:21:40 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_philo_dto	args;

	if (!(ac == 5 || ac == 6))
		handle_error();
	args = input_arguments(av);
	simulate_problem(args);
	return (0);
}
