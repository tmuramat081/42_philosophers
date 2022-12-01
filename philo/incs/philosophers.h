/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:19:30 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/02 01:33:41 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <libc.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include "philosophers.h"
# include "libft.h"

typedef struct s_philos_dto
{
	size_t	num_of_philos;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	num_of_eating;
}	t_philos_dto;

typedef struct s_philosopher
{
	int			id;
	pthread_t	thread_id;
	int			cnt_ate;
	bool		is_dead;

}	t_philosopher;

typedef struct s_arbitrator
{
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_eating;
}	t_arbitrator;

t_philos_dto	input_arguments(char **av);
void			solve_philos_problem(t_philos_dto input);
t_arbitrator	*init_waiter(t_philos_dto input);
t_philosopher	*init_philosophers(t_philos_dto input);
void			handle_error(void);

void			*lifecycle(void *data);

#endif