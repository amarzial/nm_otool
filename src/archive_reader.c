/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <amarzial@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 17:03:37 by amarzial          #+#    #+#             */
/*   Updated: 2018/09/14 15:58:53 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

int is_archive_file(const t_file_map *fm)
{
	if (!check_space(fm->ptr, SARMAG))
		return (0);
	return (ft_strncmp(fm->ptr, ARMAG, SARMAG) == 0);
}

static void *cleanup(t_list **lst)
{
	ft_lstdel(lst, delete_list);
	return (NULL);
}

t_list *get_archive_list(const t_file_map *fm)
{
	t_list *	   file_lst;
	t_list *	   tmp;
	int			   member_size;
	size_t		   offset;
	struct ar_hdr *member_header;

	offset = SARMAG;
	file_lst = NULL;
	while (offset < fm->size)
	{
		if (!check_space((char *)(fm->ptr) + offset, sizeof(struct ar_hdr)))
			return (cleanup(&file_lst));
		member_header = (struct ar_hdr *)((char *)(fm->ptr) + offset);
		if (file_lst == NULL)
			file_lst = tmp = ft_lstnew(&member_header, sizeof(struct ar_hdr *));
		else
		{
			tmp->next = ft_lstnew(&member_header, sizeof(struct ar_hdr *));
			tmp = tmp->next;
		}
		member_size = atoi(member_header->ar_size);
		offset += sizeof(struct ar_hdr) + member_size;
	}
	return file_lst;
}

char *get_file_name(void *ptr)
{
	struct ar_hdr *header;
	char *		   name;
	size_t		   name_size;

	header = (struct ar_hdr *)ptr;
	name = NULL;
	if (ft_strncmp("#1/", header->ar_name, 3) == 0)
	{
		name_size = ft_atoi((char *)header->ar_name + 3);
		name = ft_strnew(name_size);
		if (name == NULL)
			return (NULL);
		ft_strncpy(name, (char *)ptr + sizeof(struct ar_hdr), name_size);
	}
	else
	{
		if ((name = ft_strnew(16)) == NULL)
			return (NULL);
		ft_strncpy(name, header->ar_name, 16);
	}
	return name;
}

void *get_file_begin(void *ptr)
{
	struct ar_hdr *header;
	size_t		   name_size;

	header = (struct ar_hdr *)ptr;
	if (ft_strncmp("#1/", header->ar_name, 3) == 0)
	{
		name_size = ft_atoi((char *)header->ar_name + 3);
		return ((char *)ptr + sizeof(struct ar_hdr) + name_size);
	}
	return ((char *)ptr + sizeof(struct ar_hdr));
}
