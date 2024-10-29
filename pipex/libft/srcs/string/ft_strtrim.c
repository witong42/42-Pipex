/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:23:45 by witong            #+#    #+#             */
/*   Updated: 2024/10/02 09:27:01 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*str;
	int		i;
	int		end;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	end = ft_strlen(s1);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (i < end && ft_strchr(set, s1[end - 1]))
		end--;
	str = ft_substr(s1, i, end - i);
	return (str);
}
