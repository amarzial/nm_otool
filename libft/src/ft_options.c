/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 11:39:50 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/20 18:08:15 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_options.h"

#include "libft.h"

int		ft_opt_add(t_options *opt, const char *name, int args)
{
	t_list	*tmp;
	t_opt	topt;

	if ((topt.opt = ft_strdup(name)) == NULL)
		return (OPT_BAD_ALLOC);
	topt.nargs = args;
	topt.args = NULL;
	topt.used = 0;
	if ((tmp = ft_lstnew(&topt, sizeof(topt))) == NULL)
		return (OPT_BAD_ALLOC);
	ft_lstadd(opt, tmp);
	return (OPT_OK);
}

int		ft_opt_parse(t_options opt, int ac, const char **av, int *pos)
{
	int			i;
	t_options	t;
	int			status;

	i = 0;
	while (i < ac)
	{
		t = opt;
		if ((t = opt_find(opt, av[i])) == NULL)
			break ;
		if ((status = insert_args(t, &i, ac, av)) != OPT_OK)
			return (status);
		++i;
	}
	*pos = i;
	return (OPT_OK);
}

int		ft_opt_get(t_options opt, char *name, char ***dest)
{
	t_opt *var;

	while (opt != NULL)
	{
		var = (t_opt*)opt->content;
		if (ft_strcmp(var->opt, name) == 0 && var->used)
		{
			if (dest != NULL)
				*dest = var->args;
			return (var->used);
		}
		opt = opt->next;
	}
	return (0);
}

void	ft_opt_clear(t_options *opt)
{
	ft_lstdel(opt, cleaner);
}

void	ft_opt_print(t_options opt)
{
	char	**args;
	t_opt	*val;

	ft_printf("Options:\n");
	while (opt != NULL)
	{
		val = (t_opt*)opt->content;
		if (val->used)
		{
			ft_printf("\t%s (%d):", val->opt, val->nargs);
			if (val->nargs != 0 && val->args != NULL)
			{
				args = val->args;
				while (*args != NULL)
				{
					ft_printf(" %s", *args);
					++args;
				}
			}
			ft_putstr("\n");
		}
		opt = opt->next;
	}
}
