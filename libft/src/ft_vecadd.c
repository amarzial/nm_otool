/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 20:19:55 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/19 16:17:48 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_vecadd(t_vector *vec, const void *data)
{
	if (vec->size == vec->capacity)
	{
		if (!ft_vecreserve(vec, vec->capacity * 2))
			return (0);
	}
	ft_memcpy(((char *)vec->data) + (vec->size * vec->element_size), data, \
			vec->element_size);
	++(vec->size);
	return (1);
}
