/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:20:32 by witong            #+#    #+#             */
/*   Updated: 2024/10/02 09:25:17 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len = 1;
	else if (n < 0)
	{
		len++;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*array;
	int		len;
	int		neg;

	neg = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n = -n;
		neg = 1;
	}
	len = ft_intlen(n);
	array = (char *)malloc(sizeof(char) * (len + 1 + neg));
	if (!array)
		return (NULL);
	array[len + neg] = '\0';
	while (len-- > 0)
	{
		array[len + neg] = n % 10 + '0';
		n /= 10;
	}
	if (neg == 1)
		array[0] = '-';
	return (array);
}
