/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 18:47:39 by amarzial          #+#    #+#             */
/*   Updated: 2018/05/15 19:35:47 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_H
#define INTERNAL_H

#include "libft.h"

#include <ar.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <stddef.h>
#include <sys/mman.h>
#include <unistd.h>

#define FT_MACH32 1
#define FT_MACH64 2
#define FT_MACHUN 4

typedef struct mach_header_64     t_header64;
typedef struct segment_command_64 t_command64;
typedef struct section_64         t_section64;
typedef struct load_command       t_loadcmd;
typedef struct symtab_command     t_symtabcmd;
typedef struct nlist_64           t_nlist;

typedef struct s_file_map
{
    void * ptr;
    size_t size;
} t_file_map;

int map_file(char *filename, t_file_map *map);

void delete_list(void *p, size_t size);

int is_archive_file(const t_file_map *fm);
t_list *get_archive_list(const t_file_map *fm);
char *get_file_name(void *ptr);
void *get_file_begin(void *ptr);

#endif
