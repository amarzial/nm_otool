/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 17:03:37 by amarzial          #+#    #+#             */
/*   Updated: 2018/05/15 19:33:30 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

int is_archive_file(const t_file_map *fm)
{
	return (ft_strncmp(fm->ptr, ARMAG, SARMAG) == 0);
}

t_list *get_archive_list(const t_file_map *fm)
{
	t_list *	   file_list;
	t_list *	   tmp;
	int			   member_size;
	size_t		   offset;
	struct ar_hdr *member_header;

	offset = SARMAG;
	file_list = NULL;
	while (offset < fm->size)
	{
		member_header = (struct ar_hdr *)((char *)(fm->ptr) + offset);
		if (file_list == NULL)
			file_list = tmp =
				ft_lstnew(&member_header, sizeof(struct ar_hdr *));
		else
		{
			tmp->next = ft_lstnew(&member_header, sizeof(struct ar_hdr *));
			tmp = tmp->next;
		}
		member_size = atoi(member_header->ar_size);
		offset += sizeof(struct ar_hdr) + member_size;
	}
	return file_list;
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
