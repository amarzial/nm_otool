/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <amarzial@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 19:25:16 by amarzial          #+#    #+#             */
/*   Updated: 2018/09/18 18:39:06 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void	delete_list(void *p, size_t size)
{
	(void)size;
	if (p)
		free(p);
}

int		is_mach_o(void *ptr)
{
	uint32_t magic;

	if (!check_space(ptr, sizeof(uint32_t)))
		return (FT_MACHNO);
	magic = *(uint32_t *)ptr;
	if (magic == MH_MAGIC)
		return (check_space(ptr, sizeof(t_header32)) ? FT_MACH32 : FT_MACHNO);
	else if (magic == MH_MAGIC_64)
		return (check_space(ptr, sizeof(t_header64)) ? FT_MACH64 : FT_MACHNO);
	else if (magic == FAT_CIGAM)
		return (check_space(ptr, sizeof(t_fat_header)) ? FT_MACHUN : FT_MACHNO);
	return (FT_MACHNO);
}
