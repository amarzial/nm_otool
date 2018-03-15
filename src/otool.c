/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 14:09:47 by amarzial          #+#    #+#             */
/*   Updated: 2018/03/15 12:56:16 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "internal.h"
#include "libft.h"

typedef struct mach_header_64     t_header64;
typedef struct segment_command_64 t_command64;
typedef struct section_64         t_segment64;

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
    ft_printf("Command:%#x\n  cmd: %u\n  cmdsize: %u\n  \
segname: %s\n  vmaddr: %llu\n  vmsize: %llu\n  fileoff: %llu\n  \
filesize: %llu\n  maxprot: %u\n  initprot: %u\n  nsects: %u\n  flags: %u\n", of,
              c->cmd, c->cmdsize, segname, c->vmaddr, c->vmsize, c->fileoff, c->filesize, c->maxprot, c->initprot, c->nsects, c->flags);
}

t_segment64 *get_text_segment(t_command64 *c)
{
    t_segment64     *seg;
    unsigned int    i;

    i = 0;
    seg = NULL;
    while (i < c->nsects)
    {
        seg = (void*)((char*)c + sizeof(t_command64) + (i * sizeof(t_segment64)));
        ft_printf("sectname: %.16s, segname: %.16s\n", seg->sectname, seg->segname);
                    ++i;
    }
    return seg;
}

int main(int argc, char **argv)
{
    t_file_map   map;
    t_header64   *h64;
    t_command64  *s64;
    unsigned int cmds;
    size_t       offset;

    if (argc != 2)
        return (-1);
    if (!map_file(argv[1], &map))
    {
        h64 = map.ptr;
        if (h64)
        {
            print_header_64(h64);
            offset = sizeof(t_header64);
            cmds = 0;
            while (cmds < h64->ncmds)
            {
                s64 = (void *) ((char *) map.ptr + offset);
                if (s64->cmd == LC_SEGMENT_64)
                {
                    get_text_segment(s64);
                    break;
                }
                print_command_64(s64, offset);
                offset += s64->cmdsize;
                ++cmds;
            }
        }
    }

    return (0);
}
