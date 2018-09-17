/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecreserve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 22:03:42 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/19 16:16:59 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_vecreserve(t_vector *vec, size_t size)
{
	void *new;

	if (size > vec->size)
	{
		if ((new = realloc(vec->data, size * vec->element_size)) == NULL)
		{
			return (0);
		}
		vec->data = new;
		vec->capacity = size;
	}
	return (1);
}
