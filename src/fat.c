/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <amarzial@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 17:53:19 by amarzial          #+#    #+#             */
/*   Updated: 2018/09/11 12:24:29 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

uint32_t big_read(uint32_t n)
{
	uint32_t val;
	int i;

	val = 0;
	i = 0;
	while (i < 4)
	{
		val <<= 8;
		val |= (n & 0xFF);
		n >>= 8;
		++i;
	}
	return (val);
}

static void set_best(void *ptr, uint32_t offset, uint32_t *res, int *current)
{
	uint32_t *magic;

	magic = (uint32_t*)((char*)ptr + offset);
	if (*magic == MH_MAGIC && *current != FT_MACH64)
	{
		*current = FT_MACH32;
		*res = offset;
	}
	else if (*magic == MH_MAGIC_64)
	{
		*current = FT_MACH64;
		*res = offset;
	}
}

int fat_get_best(void **ptr)
{
	t_fat_header *hdr;
	t_fat_arch	*arch;
	uint32_t narch;
	uint32_t i;
	int best_arch;
	uint32_t best_offset;

	i = 0;
	hdr = (t_fat_header*)(*ptr);
	narch = big_read(hdr->nfat_arch);
	best_arch = FT_MACHNO;
	best_offset = 0;
	while (i < narch) {
		arch = (t_fat_arch*)((char*)(*ptr) + sizeof(t_fat_header)\
			+ (sizeof(t_fat_arch) * i));
		set_best(*ptr, big_read(arch->offset), &best_offset, &best_arch);
		++i;
	}
	*ptr = ((char*)*ptr) + best_offset;
	return (best_arch);
}
