/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <amarzial@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 12:07:40 by amarzial          #+#    #+#             */
/*   Updated: 2018/09/17 14:18:49 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal.h>

static t_file_map *g_current_file;

void	set_current_file(t_file_map *map)
{
	g_current_file = map;
}

int		check_space(void *ptr, size_t size)
{
	if (!ptr || !g_current_file)
		return (0);
	return (
		g_current_file->size - ((char *)ptr - (char *)g_current_file->ptr) >=
		size);
}
