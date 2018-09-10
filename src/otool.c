/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 14:09:47 by amarzial          #+#    #+#             */
/*   Updated: 2018/05/29 18:34:20 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"
#include "libft.h"
#include <mach-o/loader.h>
#include <mach-o/nlist.h>

void print_header_64(t_header64 *h)
{
	ft_printf(
		"Mach-o 64 header:\n  Magic number: %x\n  Cpu type: %u\n  \
Cpu subtype: %u\n  Filetype: %u\n  ncmds: %u\n  sizeofcmds: %u\n  \
flags: %u\n  reserved: %u\n",
		h->magic, h->cputype, h->cpusubtype, h->filetype, h->ncmds,
		h->sizeofcmds, h->flags, h->reserved);
}

void print_command_64(t_command64 *c, size_t of)
{
	char segname[17];

	ft_memcpy(segname, c->segname, 16);
	segname[16] = '\0';
	ft_printf(
		"Command:%#x\n  cmd: %#x\n  cmdsize: %u\n  \
segname: %s\n  vmaddr: %llu\n  vmsize: %llu\n  fileoff: %llu\n  \
filesize: %llu\n  maxprot: %u\n  initprot: %u\n  nsects: %u\n  flags: %u\n",
		of, c->cmd, c->cmdsize, segname, c->vmaddr, c->vmsize, c->fileoff,
		c->filesize, c->maxprot, c->initprot, c->nsects, c->flags);
}

void print_mem(void *mem, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		if (i % 0x10 == 0)
			ft_printf("%016llx\t", i);
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
			print_mem((char *)begin + seg->offset, seg->size);
		}
		++i;
	}
	return seg;
}

void print_symtab(struct load_command *lc, void *begin)
{
	struct symtab_command *sc;
	struct nlist_64 *	  nlist;
	unsigned int		   i;

	sc = (struct symtab_command *)lc;
	i = 0;
	nlist = (struct nlist_64 *)((char *)begin + sc->symoff);
	while (i < sc->nsyms)
	{
		ft_printf("%s\n", (char *)begin + (sc->stroff + nlist->n_un.n_strx));
		ft_printf(
			"  type: %#.2x\n  sect: %d\n  desc: %#.4x\n  value: %#.16x\n",
			nlist->n_type, nlist->n_sect, nlist->n_desc, nlist->n_value);
		nlist = (struct nlist_64 *)((char *)nlist + sizeof(struct nlist_64));
		++i;
	}
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
