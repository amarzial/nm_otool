/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_symbol_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 14:40:56 by amarzial          #+#    #+#             */
/*   Updated: 2018/03/28 17:10:11 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void delete_list(void *p, size_t size)
{
    (void) size;
    if (p)
        free(p);
}

static char get_symbol_type(const t_nlist *nlist, t_list *slist)
{
    char          l;
    unsigned char t;
    size_t        slist_len;

    slist_len = ft_lstlen(slist);
    t = (nlist->n_type & N_TYPE);
    if (t == N_UNDF)
        l = 'u';
    else if (t == N_ABS)
        l = 'a';
    else if (t == N_SECT)
        l = get_section(slist, nlist->n_sect, slist_len);
    else if (t == N_INDR)
        l = 'i';
    else
        l = '#';

    return ((nlist->n_type & N_EXT) ? ft_toupper(l) : l);
}

static void print_symbols(const void *begin, const t_symtabcmd *tab, t_list *slist)
{
    t_nlist *    lst;
    unsigned int i;
    t_symbol     symbol;
    t_list       *symlist;

    i = tab->nsyms;
    lst = (t_nlist *) ((char *) begin + tab->symoff);
    symlist = NULL;
    while (i--)
    {
        symbol.has_value = 0;
        if ((lst->n_type & N_TYPE) != N_UNDF)
        {
            symbol.has_value = 1;
            symbol.value = lst->n_value;
        }
        symbol.type = get_symbol_type(lst, slist);
        symbol.name = (char *) begin + tab->stroff + lst->n_un.n_strx;
        ft_lstadd(&symlist, ft_lstnew(&symbol, sizeof(t_symbol)));
        lst = (t_nlist *) ((char *) lst + sizeof(t_nlist));
    }
    sort_and_print(symlist);
    ft_lstdel(&symlist, delete_list);
}

// DYSYMTAB too?
void print_symtab(const void *begin, size_t ncmds)
{
    t_loadcmd *  cmd;
    t_symtabcmd *symtab;
    t_list *     slist;

    cmd = (t_loadcmd *) ((char *) begin + sizeof(t_header64));
    slist = NULL;
    while (ncmds--)
    {
        if (cmd->cmd == LC_SEGMENT_64)
        {
            store_sections((t_command64 *) cmd, &slist);
        }
        if (cmd->cmd == LC_SYMTAB)
        {
            symtab = (t_symtabcmd *) cmd;
        }
        cmd = (t_loadcmd *) ((char *) cmd + cmd->cmdsize);
    }
    print_symbols(begin, symtab, slist);
    ft_lstdel(&slist, delete_list);
}
