/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 18:47:39 by amarzial          #+#    #+#             */
/*   Updated: 2018/03/06 12:54:26 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_H
#define INTERNAL_H

#include <stddef.h>
#include <sys/mman.h>
#include <unistd.h>

typedef struct s_file_map
{
    void * ptr;
    size_t size;
} t_file_map;

int map_file(char *filename, t_file_map *map);

#endif
