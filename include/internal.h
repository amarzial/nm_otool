/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 18:47:39 by amarzial          #+#    #+#             */
/*   Updated: 2018/03/22 14:50:59 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_H
#define INTERNAL_H

#include <stddef.h>
#include <sys/mman.h>
#include <unistd.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>

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

#endif
