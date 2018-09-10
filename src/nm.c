/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <amarzial@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 17:15:47 by amarzial          #+#    #+#             */
/*   Updated: 2018/09/11 12:46:58 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "internal.h"
#include "libft.h"

static void print_symtab_handler(void *ptr, int arch)
{
	void *data;

	data = ptr;
	if (arch == FT_MACHUN)
	{
		arch = fat_get_best(&data);
	}
	
	if (arch == FT_MACH32)
		print_symtab_32(data);
	else if (arch == FT_MACH64)
		print_symtab_64(data);
	return ;
}

static void handle_file(t_list *current, t_list *lst, \
	const char *archive_file) {
	void *  begin;
	char *filename;
	int	arch;

	begin = get_file_begin(*(void **)current->content);
	if ((arch = is_mach_o(begin)))
	{
		if ((filename = get_file_name(*(void **)(current->content))) ==
			NULL)
			return; // memory error?
		if (current != lst)
			ft_printf("\n");
		ft_printf("%s(%s):\n", archive_file, filename);
		free(filename);
		print_symtab_handler(get_file_begin(*(void **)current->content), arch);
	}
}

static void handle_archive(t_file_map *fm, const char *archive_file)
{
	t_list *lst;
	t_list *current;

	if ((current = lst = get_archive_list(fm)) == NULL)
		return;
	ft_printf("The archive contains %d files\n", ft_lstlen(lst));
	while (current != NULL)
	{
		handle_file(current, lst, archive_file);
		current = current->next;
	}
	ft_lstdel(&lst, delete_list);
}

int main(int argc, char **argv)
{
	t_file_map	map;
	int			arch;

	if (argc != 2)
		return (-1);
	if (!map_file(argv[1], &map))
	{
		if ((arch = is_mach_o(map.ptr)))
			print_symtab_handler(map.ptr, arch);
		else if (is_archive_file(&map))
			handle_archive(&map, argv[1]);
		else
		{
			ft_printf("Not a Mach-O file\n");
			return (-1);
		}
	}

	return (0);
}
