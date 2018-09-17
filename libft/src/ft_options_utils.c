/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_options_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 14:45:07 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/28 11:24:53 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_options.h"

t_options	opt_find(t_options opts, const char *str)
{
	t_opt *val;

	while (opts != NULL)
	{
		val = (t_opt*)opts->content;
		if (ft_strcmp(val->opt, str) == 0)
			break ;
		opts = opts->next;
	}
	return (opts);
}

static int	expand_args(t_opt *opt, int size, int *pos)
{
	int		current;
	char	**args;

	current = 0;
	args = opt->args;
	while (args && args[current] != NULL)
		++current;
	if ((args = (char**)realloc(opt->args, \
					sizeof(char*) * (current + size + 1))) == NULL)
		return (0);
	opt->args = args;
	*pos = current;
	return (1);
}

int			insert_args(t_options t, int *i, int ac, const char **av)
{
	t_opt	*opt;
	int		count;
	int		size;
	int		pos;

	opt = (t_opt*)t->content;
	opt->used = 1;
	size = opt->nargs >= 0 ? opt->nargs : ac - 1 - *i;
	if (size == 0)
		return (OPT_OK);
	if (size > ac - 1 - *i)
		return (OPT_BAD_NARGS);
	if (!expand_args(opt, size, &pos))
		return (OPT_BAD_ALLOC);
	opt->args[pos + size] = NULL;
	count = 0;
	while (count < size)
	{
		*i += 1;
		if ((opt->args[pos + count++] = ft_strdup(av[*i])) == NULL)
			return (OPT_BAD_ALLOC);
	}
	return (OPT_OK);
}

void		cleaner(void *content, size_t content_size)
{
	t_opt	*opt;
	char	**args;

	if (content_size == sizeof(t_opt))
	{
		opt = (t_opt*)content;
		args = opt->args;
		if (opt->nargs != 0 && opt->args != NULL)
		{
			while (*args != NULL)
			{
				free(*args);
				++args;
			}
			free(*args);
		}
		free(opt->args);
		free(opt->opt);
	}
	free(content);
}
