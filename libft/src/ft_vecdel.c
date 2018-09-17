/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 19:01:01 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/19 16:18:18 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

void	ft_vecdel(t_vector *vec)
{
	size_t i;

	if (vec->del != NULL)
	{
		i = 0;
		while (i < vec->size)
		{
			vec->del((char *)vec->data + (i++ * vec->element_size));
		}
	}
	free(vec->data);
}
