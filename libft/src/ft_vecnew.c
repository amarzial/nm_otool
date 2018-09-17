/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 12:57:11 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/19 16:16:41 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

t_vector	ft_vecnew(size_t elem_size, void (*del)(void *))
{
	t_vector vec;

	if ((vec.data = malloc(elem_size)) == NULL)
		return (vec);
	vec.element_size = elem_size;
	vec.capacity = 1;
	vec.size = 0;
	vec.del = del == NULL ? NULL : del;
	return (vec);
}
