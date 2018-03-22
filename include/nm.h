/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 14:29:16 by amarzial          #+#    #+#             */
/*   Updated: 2018/03/22 19:29:45 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
#define NM_H

#include "libft.h"
#include "internal.h"

typedef struct  s_symbol
{
  char *name;
  char type;
  uint64_t value;
  int has_value;
}               t_symbol;

int store_sections(t_command64 *cmd, t_list **lst);
char get_section(t_list *slist, uint8_t nsect, size_t slist_len);
void print_symtab(const void *begin, size_t ncmds);
void sort_and_print(t_list *symlist);
#endif
