/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_mapper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 18:22:38 by amarzial          #+#    #+#             */
/*   Updated: 2018/03/05 18:48:39 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

#include <fcntl.h>
#include <sys/stat.h>

int             map_file(char *filename, t_file_map *map)
{
    int         fd;
    struct stat st;

    if ((fd = open(filename, O_RDONLY)) >= 3)
    {
        if (!fstat(fd, &st))
        {
            map->size = st.st_size;
            map->ptr = mmap(NULL, map->size, PROT_READ, MAP_PRIVATE, fd, 0);
            if (map->ptr != MAP_FAILED && !close(fd))
                return (0);
        }
    }
    close(fd);
    return (-1);
}
