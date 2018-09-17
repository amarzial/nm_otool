/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handlings.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzial <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 17:46:29 by amarzial          #+#    #+#             */
/*   Updated: 2018/06/19 18:15:24 by amarzial         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_internal.h"
#include "ft_printf_handler.h"

static t_handler	g_table[] =
{
	{'%', &ft_printf_char},
	{'i', &ft_printf_signed_decimal},
	{'d', &ft_printf_signed_decimal},
	{'D', &ft_printf_signed_decimal},
	{'o', &ft_printf_unsigned_octal},
	{'O', &ft_printf_unsigned_octal},
	{'u', &ft_printf_unsigned_decimal},
	{'U', &ft_printf_unsigned_decimal},
	{'x', &ft_printf_unsigned_hex},
	{'X', &ft_printf_unsigned_hex},
	{'p', &ft_printf_unsigned_hex},
	{'s', &ft_printf_string},
	{'S', &ft_printf_wstring},
	{'c', &ft_printf_char},
	{'C', &ft_printf_wchar},
	{0, 0}
};

int					ft_printf_handler(t_arg *arg, va_list *lst)
{
	int i;

	i = 0;
	while (g_table[i].conv != 0)
	{
		if (g_table[i].conv == arg->conversion)
			return (g_table[i].f(arg, lst));
		i++;
	}
	if (arg->conversion)
		ft_printf_noconv(arg, lst);
	return (0);
}
