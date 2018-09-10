/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <amarzial@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 19:25:16 by amarzial          #+#    #+#             */
/*   Updated: 2018/09/10 18:28:21 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void delete_list(void *p, size_t size)
{
	(void)size;
	if (p)
		free(p);
}

int is_mach_o(void *ptr)
{
	uint32_t magic;

	magic = *(uint32_t *)ptr;
	if (magic == MH_MAGIC)
		return (FT_MACH32);
	else if (magic == MH_MAGIC_64)
		return (FT_MACH64);
	else if (magic == FAT_CIGAM)
		return (FT_MACHUN);

	return (FT_MACHNO);
}
