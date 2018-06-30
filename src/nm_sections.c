/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_sections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <amarzial@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 14:44:00 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/30 13:13:00 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

/*
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
*/

char get_section(t_list *slist, uint8_t nsect, size_t slist_len)
{
    t_section64 *sect;

    while (slist && slist_len-- > nsect)
    {
        slist = slist->next;
    }
    sect = (t_section64 *) (*(t_section64 **) (slist->content));
    if (ft_strncmp(sect->sectname, SECT_TEXT, 16) == 0)
        return ('t');
    else if (ft_strncmp(sect->sectname, SECT_DATA, 16) == 0)
        return ('d');
    else if (ft_strncmp(sect->sectname, SECT_BSS, 16) == 0)
        return ('b');
    else if (ft_strncmp(sect->sectname, SECT_COMMON, 16) == 0)
        return ('s');
    else
        return ('s');
}

int store_sections(t_command64 *cmd, t_list **lst)
{
    uint32_t     n_sects;
    t_section64 *sect;

    sect = (t_section64 *) ((char *) cmd + sizeof(t_command64));
    n_sects = cmd->nsects;
    while (n_sects--)
    {
        ft_lstadd(lst, ft_lstnew(&sect, sizeof(t_section64 *)));
        sect = (t_section64 *) ((char *) sect + sizeof(t_section64));
    }
    return (1);
}
