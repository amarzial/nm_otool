/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 17:15:47 by amarzial          #+#    #+#             */
/*   Updated: 2018/03/22 19:39:59 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "internal.h"
#include "libft.h"

void print_header_64(t_header64 *h)
{
    ft_printf("Mach-o 64 header:\n  Magic number: %x\n  Cpu type: %u\n  \
Cpu subtype: %u\n  Filetype: %u\n  ncmds: %u\n  sizeofcmds: %u\n  \
flags: %u\n  reserved: %u\n",
              h->magic, h->cputype, h->cpusubtype, h->filetype, h->ncmds, h->sizeofcmds, h->flags, h->reserved);
}

void print_command_64(t_command64 *c, size_t of)
{
    char segname[17];

    ft_memcpy(segname, c->segname, 16);
    segname[16] = '\0';
    ft_printf("Command:%#x\n  cmd: %#x\n  cmdsize: %u\n  \
segname: %s\n  vmaddr: %llu\n  vmsize: %llu\n  fileoff: %llu\n  \
filesize: %llu\n  maxprot: %u\n  initprot: %u\n  nsects: %u\n  flags: %u\n",
              of, c->cmd, c->cmdsize, segname, c->vmaddr, c->vmsize, c->fileoff, c->filesize, c->maxprot, c->initprot, c->nsects, c->flags);
}

int main(int argc, char **argv)
{
    t_file_map  map;
    t_header64 *h64;

    if (argc != 2)
        return (-1);
    if (!map_file(argv[1], &map))
    {
        h64 = map.ptr;
        if (h64)
        {
            //print_header_64(h64);
            print_symtab(map.ptr, h64->ncmds);
        }
    }

    return (0);
}
