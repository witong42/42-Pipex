/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnums.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:50:39 by witong            #+#    #+#             */
/*   Updated: 2024/07/23 17:53:43 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printhexbase(unsigned long nbr, char *base)
{
	int	i;

	i = 0;
	if (nbr >= 16)
		i += ft_printhexbase(nbr / 16, base);
	i += ft_printchar(base[nbr % 16]);
	return (i);
}

int	ft_printptr(unsigned long ptr)
{
	int	i;

	i = 0;
	if (ptr == 0)
		i += ft_printstr("(nil)");
	else
	{
		i += ft_printstr("0x");
		i += ft_printhexbase(ptr, "0123456789abcdef");
	}
	return (i);
}

int	ft_printnbr(int nbr)
{
	int	i;

	i = 0;
	if (nbr == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (nbr < 0)
	{
		i += ft_printchar('-');
		nbr = -nbr;
	}
	i += ft_printuint(nbr);
	return (i);
}

int	ft_printuint(unsigned int nbr)
{
	int	i;

	i = 0;
	if (nbr >= 10)
		i += ft_printuint(nbr / 10);
	i += ft_printchar(nbr % 10 + '0');
	return (i);
}

int	ft_printhex(unsigned int hex, const char format)
{
	if (hex == 0)
		return (ft_printchar('0'));
	if (format == 'x')
		return (ft_printhexbase(hex, "0123456789abcdef"));
	else if (format == 'X')
		return (ft_printhexbase(hex, "0123456789ABCDEF"));
	else
		return (0);
}
