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
#include "ft_deque.h"

int	main(int ac, char **av)
{
	t_philo_dto	args;

	if (!(ac == 5 || ac == 6))
		handle_error();
	args = input_arguments(av);
	simulate_problem(args);
	return (0);
}

/* FIFO queue test
int main (void)
{
	t_deque		*queue;
	size_t		data;

	queue = ft_deque_init(sizeof(size_t), 10);
	ft_deque_push_back(queue, &(size_t){1});
	ft_deque_push_back(queue, &(size_t){2});
	ft_deque_push_back(queue, &(size_t){3});
	ft_deque_pop_front(queue, &data);
	printf("%zu\n", data);
	ft_deque_pop_front(queue, &data);
	printf("%zu\n", data);
	ft_deque_pop_front(queue, &data);
	printf("%zu\n", data);
	ft_deque_pop_front(queue, &data);
	printf("%zu\n", data);
	return (0);
}
*/