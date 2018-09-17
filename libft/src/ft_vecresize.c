/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecresize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 22:02:55 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/19 16:18:32 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	vecclear(t_vector *vec, size_t pos, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		vec->del((char *)vec->data + ((pos + i) * vec->element_size));
		++i;
	}
}

int			ft_vecresize(t_vector *vec, size_t size)
{
	size_t old;

	if (vec->size == size)
	{
		return (1);
	}
	else if (vec->size < size)
	{
		old = vec->size;
		if (!ft_vecreserve(vec, size))
			return (0);
		ft_bzero((char *)vec->data + (old * vec->element_size), \
				(size - old) * vec->element_size);
	}
	else
	{
		if (vec->del != NULL)
			vecclear(vec, vec->size, size - vec->size);
	}
	vec->size = size;
	return (1);
}
