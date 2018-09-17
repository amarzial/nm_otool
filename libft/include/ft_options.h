/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_options.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 11:39:47 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/20 18:07:48 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OPTIONS_H
# define FT_OPTIONS_H

# include "libft.h"

# define OPT_OK 0
# define OPT_BAD_NARGS 1
# define OPT_BAD_ALLOC 2

typedef struct	s_opt
{
	char	*opt;
	char	**args;
	int		nargs;
	int		used;
}				t_opt;

t_options		opt_find(t_options opts, const char *str);
int				insert_args(t_options t, int *i, int ac, const char **av);
void			cleaner(void *content, size_t content_size);

#endif
