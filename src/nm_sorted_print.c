/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_sorted_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 15:48:43 by amarzial          #+#    #+#             */
/*   Updated: 2018/03/22 19:39:01 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int compare_symbol(t_symbol *s1, t_symbol *s2)
{
    return (ft_strcmp(s1->name, s2->name));
}

static void swap_nodes(t_list *n1, t_list *n2)
{
    t_list tmp;

    tmp.content = n1->content;
    tmp.content_size = n1->content_size;
    n1->content = n2->content;
    n1->content_size = n2->content_size;
    n2->content = tmp.content;
    n2->content_size = tmp.content_size;
}

static void sort_list(t_list *symlist)
{
    t_list * cur;
    int      sorted;

    sorted = 0;
    while (!sorted)
    {
        sorted = 1;
        cur = symlist;
        while (cur)
        {
            if (cur->next)
            {
                if (compare_symbol(cur->content, cur->next->content) > 0)
                {
                    swap_nodes(cur, cur->next);
                    sorted = 0;
                }
            }
            cur = cur->next;
        }
    }
}

void sort_and_print(t_list *symlist)
{
    t_symbol *symbol;

    sort_list(symlist);
    while (symlist)
    {
        symbol = (t_symbol*)symlist->content;
        if (!symbol->has_value)
            ft_printf("                ");
        else
            ft_printf("%.16x", symbol->value);

        ft_printf(" %c %s\n", symbol->type, symbol->name);
        symlist = symlist->next;
    }
}
