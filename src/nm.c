/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 17:15:47 by amarzial          #+#    #+#             */
/*   Updated: 2018/03/17 17:56:22 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"
#include "libft.h"
#include <mach-o/loader.h>
#include <mach-o/nlist.h>

typedef struct mach_header_64     t_header64;
typedef struct segment_command_64 t_command64;
typedef struct section_64         t_section64;
typedef struct load_command       t_loadcmd;
typedef struct symtab_command     t_symtabcmd;
typedef struct nlist_64             t_nlist;

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

t_section64 *get_text_section(t_command64 *c)
{
    t_section64 *seg;
    unsigned int i;

    i = 0;
    seg = NULL;
    while (i < c->nsects)
    {
        seg = (void *) ((char *) c + sizeof(t_command64) + (i * sizeof(t_section64)));
        ft_printf("sectname: %.16s, segname: %.16s\n", seg->sectname, seg->segname);
        ++i;
    }
    return seg;
}

/*static void print_symtab(struct load_command *lc, void *begin)
{
    struct symtab_command *sc;
    struct nlist_64 *      nlist;
    unsigned int           i;

    sc = (struct symtab_command *) lc;
    i = 0;
    nlist = (struct nlist_64 *) ((char *) begin + sc->symoff);
    while (i < sc->nsyms)
    {
        ft_printf("%s\n", (char *) begin + (sc->stroff + nlist->n_un.n_strx));
        ft_printf("  type: %#.2x\n  sect: %d\n  desc: %#.4x\n  value: %#.16x\n",
                  nlist->n_type, nlist->n_sect, nlist->n_desc, nlist->n_value);
        nlist = (struct nlist_64 *) ((char *) nlist + sizeof(struct nlist_64));
        ++i;
    }
}*/

static void print_symbols(const void *begin, const t_symtabcmd *tab)
{
    t_nlist *    lst;
    unsigned int i;

    i = tab->nsyms;
    lst = (t_nlist *) ((char *) begin + tab->symoff);
    while (i--)
    {
        if ((lst->n_type & N_TYPE) == N_UNDF)
            ft_printf("                ");
        else
            ft_printf("%.16x", lst->n_value);

        ft_printf(" t %s\n", (char *) begin + tab->stroff + lst->n_un.n_strx);
        lst = (t_nlist *) ((char *) lst + sizeof(t_nlist));
    }
}

// DYSYMTAB too?
static void print_symtab(const void *begin, size_t ncmds)
{
    t_loadcmd *  cmd;
    t_symtabcmd *symtab;

    cmd = (t_loadcmd *) ((char *) begin + sizeof(t_header64));
    while (ncmds--)
    {
        if (cmd->cmd == LC_SYMTAB)
        {
            symtab = (t_symtabcmd *) cmd;
            print_symbols(begin, symtab);
        }
        cmd = (t_loadcmd *) ((char *) cmd + cmd->cmdsize);
    }
}

int main(int argc, char **argv)
{
    t_file_map           map;
    t_header64 *         h64;

    if (argc != 2)
        return (-1);
    if (!map_file(argv[1], &map))
    {
        h64 = map.ptr;
        if (h64)
        {
            print_header_64(h64);
            print_symtab(map.ptr, h64->ncmds);
        }
    }

    return (0);
}
