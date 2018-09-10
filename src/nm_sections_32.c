/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_sections_32.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <amarzial@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 14:44:00 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/30 13:13:00 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

char get_section_32(t_list *slist, uint8_t nsect, size_t slist_len)
{
    t_section32 *sect;

    while (slist && slist_len-- > nsect)
    {
        slist = slist->next;
    }
    sect = (t_section32 *)(*(t_section32 **)(slist->content));
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

int store_sections_32(t_command32 *cmd, t_list **lst)
{
    uint32_t     n_sects;
    t_section32 *sect;

    sect = (t_section32 *)((char *)cmd + sizeof(t_command32));
    n_sects = cmd->nsects;
    while (n_sects--)
    {
        ft_lstadd(lst, ft_lstnew(&sect, sizeof(t_section32 *)));
        sect = (t_section32 *)((char *)sect + sizeof(t_section32));
    }
    return (1);
}
