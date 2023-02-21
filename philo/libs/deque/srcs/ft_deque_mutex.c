#include "ft_deque.h"

void    deque_lock(t_deque *deque)
{
    pthread_mutex_lock(&deque->mutex);
}

void deque_unlock(t_deque * deque) 
{
    pthread_mutex_unlock(&deque->mutex);
}