#include "philosophers.h"
#include "ft_deque.h"

bool	wait_ms(t_arbitrator *waiter)
{
	usleep(100);
	if (waiter->monitor->is_any_died == true)
		return (false);
	return (true);
}

void	*server(void	*p_waiter)
{
	t_arbitrator	*waiter;

	waiter = p_waiter;
	while (wait_ms(waiter))
		;
	return (NULL);
}

void	send_message(t_philosopher *philo)
{
	t_arbitrator	*waiter;

	waiter = philo->waiter;
	ft_deque_lock(waiter->queue);
	ft_deque_push_back(waiter->queue, &philo->id);
	ft_deque_unlock(waiter->queue);
}

void	receive_message(t_philosopher *philo)
{
	t_arbitrator	*waiter;
	size_t			*top;

	waiter = philo->waiter;
	while (wait_ms(waiter))
	{
		top = ft_deque_front(waiter->queue);
		if (top && *top == philo->id)
		{
			ft_deque_lock(waiter->queue);
			ft_deque_pop_back(waiter->queue, top);
			ft_deque_unlock(waiter->queue);
			break ;
		}
	}
}
