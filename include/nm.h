/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 14:29:16 by amarzial          #+#    #+#             */
/*   Updated: 2018/05/15 19:36:40 by amarzial         ###   ########.fr       */
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

int store_sections_32(t_command32 *cmd, t_list **lst);
char get_section_32(t_list *slist, uint8_t nsect, size_t slist_len);
void print_symtab_32(const void *ptr);

int store_sections_64(t_command64 *cmd, t_list **lst);
char get_section_64(t_list *slist, uint8_t nsect, size_t slist_len);
void print_symtab_64(const void *ptr);

void sort_and_print(t_list *symlist, size_t size);
#endif
