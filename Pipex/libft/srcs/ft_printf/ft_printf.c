/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:12:59 by witong            #+#    #+#             */
/*   Updated: 2024/07/23 18:26:11 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_format_check(va_list *args, const char format)
{
	if (format == 'c')
		return (ft_printchar(va_arg(*args, int)));
	else if (format == 's')
		return (ft_printstr(va_arg(*args, char *)));
	else if (format == 'p')
		return (ft_printptr(va_arg(*args, unsigned long)));
	else if (format == 'd' || format == 'i')
		return (ft_printnbr(va_arg(*args, int)));
	else if (format == 'u')
		return (ft_printuint(va_arg(*args, unsigned int)));
	else if (format == 'x' || format == 'X')
		return (ft_printhex(va_arg(*args, unsigned int), format));
	else if (format == '%')
		return (ft_printchar('%'));
	else
	{
		ft_printchar('%');
		ft_printchar(format);
		return (2);
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (!format[i])
				return (-1);
			len += ft_format_check(&args, format[i]);
		}
		else
			len += ft_printchar(format[i]);
		i++;
	}
	va_end(args);
	return (len);
}
