/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                  +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 00:57:00 by tmuramat          #+#    #+#             */
/*   Updated: 2023/02/23 18:32:02 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_valid_arguments(t_philo_dto *args)
{
	if (args->num_of_philos > 200)
		return (false);
	else if (args->time_to_die > 1000)
		return (false);
	else if (args->time_to_eat > 1000)
		return (false);
	else if (args->time_to_sleep > 1000)
		return (false);
	else if (args->num_of_eating > 1000)
		return (false);
	return (true);
}

/** Convert string to int value, using strtol function. */
bool	convert_str_to_int(char *str, long *num)
{
	char	*end_ptr;
	long	long_num;

	end_ptr = NULL;
	long_num = ft_strtol_d(str, &end_ptr);
	if (long_num < INT_MIN || INT_MAX < long_num)
		return (false);
	else if (*end_ptr || end_ptr == str)
		return (false);
	*num = long_num;
	return (true);
}

bool	input_arguments(char **av, t_philo_dto *args)
{
	if (!convert_str_to_int(av[1], &args->num_of_philos))
		return (false);
	if (!convert_str_to_int(av[2], &args->time_to_die))
		return (false);
	if (!convert_str_to_int(av[3], &args->time_to_eat))
		return (false);
	if (!convert_str_to_int(av[4], &args->time_to_sleep))
		return (false);
	if (av[5])
	{
		if (!convert_str_to_int(av[5], &args->num_of_eating))
			return (false);
	}
	else
		args->num_of_eating = -1;
	if (!is_valid_arguments(args))
		return (false);
	return (true);
}
