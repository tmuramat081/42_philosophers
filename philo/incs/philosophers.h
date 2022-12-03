/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:19:30 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/01 01:52:27 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <libc.h>
# include "libft.h"
# include "philosophers.h"

typedef struct s_dto
{
	size_t	num_of_philosophers;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	num_of_eating;
}	t_dto;

typedef struct s_philosopher
{
	size_t 		id;
	pthread_t	thread_id;

}	t_philosopher;

typedef struct s_arbitrator
{
	size_t	num_of_philos;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	num_of_eating;
}	t_arbitrator;

t_dto			input_arguments(char **av);
void			solve_philos_problem(t_dto);
t_arbitrator	*init_waiter(t_dto dto);
t_philosopher	*init_philosophers(t_dto dto);
void			handle_error(void);


#endif