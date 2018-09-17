/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <amarzial@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 14:36:08 by amarzial          #+#    #+#             */
/*   Updated: 2018/09/17 14:40:50 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>

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

typedef struct						s_file_map
{
	void	*ptr;
	size_t	size;
}									t_file_map;

#endif
