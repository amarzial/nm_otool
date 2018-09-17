/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <amarzial@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 18:47:39 by amarzial          #+#    #+#             */
/*   Updated: 2018/09/17 14:38:30 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_H
# define INTERNAL_H

# include "libft.h"

# include <ar.h>
# include <stddef.h>
# include <sys/mman.h>
# include <unistd.h>

# include "structs.h"

# define FT_MACHNO 0
# define FT_MACH32 1
# define FT_MACH64 2
# define FT_MACHUN 4

int		map_file(char *filename, t_file_map *map);
void	unmap_file(t_file_map *map);

void	delete_list(void *p, size_t size);
int		is_mach_o(void *ptr);

int		is_archive_file(const t_file_map *fm);
t_list	*get_archive_list(const t_file_map *fm);
char	*get_file_name(void *ptr);
void	*get_file_begin(void *ptr);

int		fat_get_best(void **ptr);

void	set_current_file(t_file_map *map);
int		check_space(void *ptr, size_t size);

#endif
