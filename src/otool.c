/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <amarzial@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 14:09:47 by amarzial          #+#    #+#             */
/*   Updated: 2018/09/17 14:02:10 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"
#include "internal.h"
#include "libft.h"

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

static void	print_text_section_handler(void *ptr, int arch)
{
	void *data;

	if (!ptr)
		return ;
	data = ptr;
	if (arch == FT_MACHUN)
	{
		arch = fat_get_best(&data);
	}
	if (arch == FT_MACH32)
		print_text_section_32(data);
	else if (arch == FT_MACH64)
		print_text_section_64(data);
	else
		ft_printf("Unsupported file\n");
	return ;
}

static void	handle_file(t_list *current, const char *archive_file)
{
	void	*begin;
	char	*filename;
	int		arch;

	begin = get_file_begin(*(void **)current->content);
	if ((arch = is_mach_o(begin)))
	{
		if ((filename = get_file_name(*(void **)(current->content))) == NULL)
			return ;
		ft_printf("%s(%s):\n", archive_file, filename);
		free(filename);
		print_text_section_handler(
			get_file_begin(*(void **)current->content), arch);
	}
}

static void	handle_archive(t_file_map *fm, const char *archive_file)
{
	t_list *lst;
	t_list *current;

	if ((lst = get_archive_list(fm)) == NULL)
		return ;
	current = lst;
	while (current != NULL)
	{
		handle_file(current, archive_file);
		current = current->next;
	}
	ft_lstdel(&lst, delete_list);
}

static int	otool_otool(char *filename, int showname)
{
	t_file_map	map;
	int			arch;

	if (!map_file(filename, &map))
	{
		set_current_file(&map);
		if ((arch = is_mach_o(map.ptr)))
		{
			if (showname)
				ft_printf("%s:\n", filename);
			print_text_section_handler(map.ptr, arch);
		}
		else if (is_archive_file(&map))
			handle_archive(&map, filename);
		else
		{
			ft_printf("Not a Mach-O file\n");
			return (-1);
		}
		unmap_file(&map);
	}
	return (0);
}

int			main(int argc, char **argv)
{
	int i;

	if (argc < 2)
		return (-1);
	i = 0;
	while (++i < argc)
	{
		otool_otool(argv[i], 1);
	}
	return (0);
}
