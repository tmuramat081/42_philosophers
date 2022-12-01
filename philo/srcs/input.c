/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 00:19:26 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/02 01:14:52 by tmuramat         ###   ########.fr       */
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

t_philos_dto	input_arguments(char **av)
{
	t_philos_dto	philos_dto;

	philos_dto.time_to_die = convert_str_to_int(av[2]);
	philos_dto.time_to_eat = convert_str_to_int(av[3]);
	philos_dto.time_to_sleep = convert_str_to_int(av[4]);
	if (av[5])
		philos_dto.num_of_eating = convert_str_to_int(av[5]);
	else
		philos_dto.num_of_eating = 0;
	return (philos_dto);
}