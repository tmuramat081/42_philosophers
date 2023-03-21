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

/**
 * @brief
 *
 * @param str 文字列をlong型整数に変換する
 * @param num 変換された値が格納されるアドレス
 * @return true 正常；変換に成功した
 * @return false エラー；文字列に数字以外が含まれていた、もしくはINTの境界値を超えた
 */
static bool	convert_str_to_int(char *str, long *num)
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

/**
 * @brief シミュレーション用の引数を取得する
 *
 * @param av
 * @param args
 * @return true 取得に成功した
 * @return false エラー；取得に失敗した
 */
bool	input_arguments(char **av, t_philo_dto *args)
{
	if (!convert_str_to_int(av[1], &args->num_of_philos)
		|| args->num_of_philos > PHILO_MAX)
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
	return (true);
}
