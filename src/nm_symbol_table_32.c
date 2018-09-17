/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_symbol_table_32.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <amarzial@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 14:40:56 by amarzial          #+#    #+#             */
/*   Updated: 2018/09/17 13:49:17 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static char get_symbol_type_32(const t_nlist32 *nlist, t_list *slist)
{
    char          l;
    unsigned char t;
    size_t        slist_len;

    slist_len = ft_lstlen(slist);
    t = (nlist->n_type & N_TYPE);
    if (nlist->n_type & N_STAB)
        l = '-';
    else if (t == N_UNDF)
        l = 'u';
    else if (t == N_ABS)
        l = 'a';
    else if (t == N_SECT)
        l = get_section_32(slist, nlist->n_sect, slist_len);
    else if (t == N_INDR)
        l = 'i';
    else
        l = '#';

    return ((nlist->n_type & N_EXT) ? ft_toupper(l) : l);
}

static void print_symbols_32(
    const void *begin, const t_symtabcmd *tab, t_list *slist)
{
    t_nlist32 *   lst;
    unsigned int i;
    t_symbol     symbol;
    t_list *     symlist;

    i = tab->nsyms;
    lst = (t_nlist32 *)((char *)begin + tab->symoff);
    symlist = NULL;
    while (i--)
    {
        symbol.has_value = 0;
        if ((lst->n_type & N_TYPE) != N_UNDF)
        {
            symbol.has_value = 1;
            symbol.value = lst->n_value;
        }
        symbol.type = get_symbol_type_32(lst, slist);
        symbol.name = (char *)begin + tab->stroff + lst->n_un.n_strx;
        if (symbol.type != '-')
            ft_lstadd(&symlist, ft_lstnew(&symbol, sizeof(t_symbol)));
        lst = (t_nlist32 *)((char *)lst + sizeof(t_nlist32));
    }
    sort_and_print(symlist, 32);
    ft_lstdel(&symlist, delete_list);
}

void print_symtab_32(const void *ptr)
{
    t_loadcmd *  cmd;
    t_symtabcmd *symtab;
    t_list *     slist;
    t_header32 * hdr;
    int          ncmds;

    hdr = (t_header32 *)ptr;
    ncmds = hdr->ncmds;
    cmd = (t_loadcmd *)((char *)ptr + sizeof(t_header32));
    slist = NULL;
    while (ncmds--)
    {
        if (!check_space(cmd, sizeof(t_loadcmd)))
            break ;
        if (cmd->cmd == LC_SEGMENT)
            store_sections_32((t_command32 *)cmd, &slist);
        if (cmd->cmd == LC_SYMTAB)
            symtab = (t_symtabcmd *)cmd;
        cmd = (t_loadcmd *)((char *)cmd + cmd->cmdsize);
    }
    print_symbols_32(ptr, symtab, slist);
    ft_lstdel(&slist, delete_list);
}
