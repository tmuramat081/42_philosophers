/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 00:57:00 by tmuramat          #+#    #+#             */
/*   Updated: 2023/02/23 18:32:02 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/** Convert string to int value, using strtol function. */
int	convert_str_to_int(char *str)
{
	char	*end_ptr;
	long	long_num;

	end_ptr = NULL;
	long_num = ft_strtol_d(str, &end_ptr);
	if (long_num < INT_MIN || INT_MAX < long_num)
		handle_error();
	else if (*end_ptr || end_ptr == str)
		handle_error();
	return ((int)long_num);
}

t_philo_dto	input_arguments(char **av)
{
	t_philo_dto	args;

	args.num_of_philos = convert_str_to_int(av[1]);
	args.time_to_die = convert_str_to_int(av[2]);
	args.time_to_eat = convert_str_to_int(av[3]);
	args.time_to_sleep = convert_str_to_int(av[4]);
	if (av[5])
		args.num_of_eating = convert_str_to_int(av[5]);
	else
		args.num_of_eating = 0;
	return (args);
}