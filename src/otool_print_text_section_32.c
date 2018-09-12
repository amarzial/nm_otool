/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_print_text_section_32.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <amarzial@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 16:40:33 by amarzial          #+#    #+#             */
/*   Updated: 2018/09/12 15:57:36 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static void print_mem(void *mem, size_t size, uint64_t addr)
{
	size_t i;
	size_t offset;

	i = 0;
	while (i < size)
	{
		offset = i + addr;
		if (i % 0x10 == 0)
			ft_printf("%08lx\t", offset);
		ft_printf("%02hhx", *((char *)mem + i));
		if (i % 0x10 != 0xf)
			ft_putchar(' ');
		else
			ft_putstr(" \n");
		++i;
	}
	ft_putchar('\n');
}

static t_section32 *get_text_section(t_command32 *c, void *begin)
{
	t_section32 *seg;
	unsigned int i;

	i = 0;
	seg = NULL;
	while (i < c->nsects)
	{
		seg =
			(void
				 *)((char *)c + sizeof(t_command32) + (i * sizeof(t_section32)));
		if (ft_strcmp(seg->sectname, "__text") == 0 &&
			ft_strcmp(seg->segname, "__TEXT") == 0)
		{
			ft_printf(
				"Contents of (%.16s,%.16s) section\n", seg->segname,
				seg->sectname);
			print_mem((char *)begin + seg->offset, seg->size, seg->addr);
		}
		++i;
	}
	return seg;
}

void print_text_section_32(void *ptr)
{
	t_header32	*hdr;
	size_t		offset;
	uint32_t	cmds;
	t_loadcmd	*lc;

	hdr = ptr;
	offset = sizeof(t_header32);
	cmds = 0;
	while (cmds < hdr->ncmds)
	{
		lc = (void *)((char *)ptr + offset);
		if (lc->cmd == LC_SEGMENT)
		{
			get_text_section((t_command32 *)lc, ptr);
		}
		else if (lc->cmd == LC_SYMTAB)
		{
			// print_symtab(lc, map.ptr);
		}
		offset += lc->cmdsize;
		++cmds;
	}
}
