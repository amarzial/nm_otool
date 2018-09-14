/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <amarzial@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 18:47:39 by amarzial          #+#    #+#             */
/*   Updated: 2018/09/14 13:54:34 by amarzial         ###   ########.fr       */
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

#define FT_MACHNO 0
#define FT_MACH32 1
#define FT_MACH64 2
#define FT_MACHUN 4

typedef struct load_command			t_loadcmd;
typedef struct symtab_command		t_symtabcmd;
typedef struct fat_header			t_fat_header;
typedef struct fat_arch				t_fat_arch;

typedef struct mach_header			t_header32;
typedef struct segment_command		t_command32;
typedef struct section				t_section32;
typedef struct nlist				t_nlist32;

typedef struct mach_header_64		t_header64;
typedef struct segment_command_64	t_command64;
typedef struct section_64			t_section64;
typedef struct nlist_64				t_nlist64;

typedef struct s_file_map
{
	void * ptr;
	size_t size;
} t_file_map;

int map_file(char *filename, t_file_map *map);
void unmap_file(t_file_map *map);

void delete_list(void *p, size_t size);
int is_mach_o(void *ptr);

int is_archive_file(const t_file_map *fm);
t_list *get_archive_list(const t_file_map *fm);
char *get_file_name(void *ptr);
void *get_file_begin(void *ptr);

int fat_get_best(void **ptr);

void set_current_file(t_file_map *map);
int check_space(void *ptr, size_t size);

#endif
