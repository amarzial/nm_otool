/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 17:15:47 by amarzial          #+#    #+#             */
/*   Updated: 2018/05/15 19:43:14 by amarzial         ###   ########.fr       */
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

static int is_mach_o(void *ptr)
{
    t_header64 *h64;

    h64 = (t_header64*)ptr;
    return (h64 && h64->magic == MH_MAGIC_64);
}

static void handle_archive(t_file_map *fm)
{
    t_list *lst;
    t_list *current;
    void *  begin;
    char *  filename;

    if ((current = lst = get_archive_list(fm)) == NULL)
        return;
    ft_printf("The archive contains %d files\n", ft_lstlen(lst));
    while (current != NULL)
    {
        begin = get_file_begin(*(void **) current->content);
        if (is_mach_o(begin))
        {
            if ((filename = get_file_name(*(void **) (current->content))) == NULL)
                return; // memory error?
            ft_printf("%p, %d: %s\n", *(void **) (current->content),
                      *(void **) (current->content) - fm->ptr, filename);
            free(filename);
            print_symtab(get_file_begin(*(void **) current->content));
        }
        current = current->next;
    }
    ft_lstdel(&lst, delete_list);
}

int main(int argc, char **argv)
{
    t_file_map map;

    if (argc != 2)
        return (-1);
    if (!map_file(argv[1], &map))
    {
        if (is_mach_o(map.ptr))
            print_symtab(map.ptr);
        else if (is_archive_file(&map))
            handle_archive(&map);
        else
        {
            ft_printf("Not a Mach-O file\n");
            return (-1);
        }
    }

    return (0);
}
