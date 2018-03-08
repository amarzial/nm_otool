/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 14:09:47 by amarzial          #+#    #+#             */
/*   Updated: 2018/03/06 13:01:52 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "internal.h"
#include "libft.h"

int main(int argc, char **argv)
{
    t_file_map             map;
    struct mach_header_64 *m64;
    unsigned int           idx;

    if (argc != 2)
        return (-1);
    if (!map_file(argv[1], &map))
    {
        m64 = map.ptr;
        idx = 0;
        while (idx < map.size)
        {
            ft_printf(" %02hhx", ((char *) m64)[idx++]);
        }
    }

    return (0);
}
