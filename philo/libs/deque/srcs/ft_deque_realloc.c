/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deque_realloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <mt15hydrangea@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 21:00:07 by tmuramat          #+#    #+#             */
/*   Updated: 2022/06/11 21:00:07 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_deque.h"
#include <string.h>

static void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (malloc(size));
	if (!size)
		return (NULL);
	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	memcpy (new_ptr, ptr, size);
	free(ptr);
	ptr = new_ptr;
	return (ptr);
}

int	ft_deque_realloc(t_deque *deque)
{
	t_deque	*new_ptr;
	size_t	new_cap;
	size_t	offset;

	new_cap = deque->cap * 2;
	offset = (char *)deque->begin - (char *)deque->data;
	new_ptr = ft_realloc(deque->data, deque->data_size * new_cap);
	if (!new_ptr)
		return (DEQUE_FAILURE);
	deque->data = new_ptr;
	deque->begin = (char *)deque->data + offset;
	deque->end = (char *)deque->begin + deque->len * deque->data_size;
	deque->cap = new_cap;
	return (DEQUE_SUCCESS);
}
