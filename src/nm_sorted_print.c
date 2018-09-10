/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_sorted_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <amarzial@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 15:48:43 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/30 15:43:08 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int compare_symbol(t_symbol *s1, t_symbol *s2)
{
	int res;

	res = ft_strcmp(s1->name, s2->name);
	return (res != 0 ? res : s1->value > s2->value);
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
	t_list *cur;
	int		sorted;

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

void sort_and_print(t_list *symlist, size_t size)
{
	t_symbol *symbol;
	char *blank;

	blank = "                                ";
	sort_list(symlist);
	while (symlist)
	{
		symbol = (t_symbol *)symlist->content;
		if (!symbol->has_value)
			ft_printf("%.*s", size / 8 * 2, blank);
		else
		{
			if (size / 8 == 4)
				ft_printf("%.8lx", symbol->value);
			else
				ft_printf("%.16llx", symbol->value);
		}
		ft_printf(" %c %s\n", symbol->type, symbol->name);
		symlist = symlist->next;
	}
}
