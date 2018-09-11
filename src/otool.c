/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <amarzial@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 14:09:47 by amarzial          #+#    #+#             */
/*   Updated: 2018/09/11 15:30:19 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"
#include "libft.h"
#include <mach-o/loader.h>
#include <mach-o/nlist.h>

static void print_mem(void *mem, size_t size, uint64_t addr)
{
	size_t i;
	size_t offset;

	i = 0;
	while (i < size)
	{
		offset = i + addr;
		if (i % 0x10 == 0)
			ft_printf("%016llx\t", offset);
		ft_printf("%02hhx", *((char *)mem + i));
		if (i % 0x10 != 0xf)
			ft_putchar(' ');
		else
			ft_putchar('\n');
		++i;
	}
	ft_putchar('\n');
}

t_section64 *get_text_section(t_command64 *c, void *begin)
{
	t_section64 *seg;
	unsigned int i;

	i = 0;
	seg = NULL;
	while (i < c->nsects)
	{
		seg =
			(void
				 *)((char *)c + sizeof(t_command64) + (i * sizeof(t_section64)));
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

int main(int argc, char **argv)
{
	t_file_map			 map;
	t_header64 *		 h64;
	struct load_command *lc;
	unsigned int		 cmds;
	size_t				 offset;

	if (argc != 2)
		return (-1);
	if (!map_file(argv[1], &map))
	{
		h64 = map.ptr;
		if (h64)
		{
			// print_header_64(h64);
			offset = sizeof(t_header64);
			cmds = 0;
			while (cmds < h64->ncmds)
			{
				lc = (void *)((char *)map.ptr + offset);
				// print_command_64((t_command64 *) lc, offset);
				if (lc->cmd == LC_SEGMENT_64)
				{
					get_text_section((t_command64 *)lc, map.ptr);
				}
				else if (lc->cmd == LC_SYMTAB)
				{
					// print_symtab(lc, map.ptr);
				}
				offset += lc->cmdsize;
				++cmds;
			}
		}
	}

	return (0);
}
