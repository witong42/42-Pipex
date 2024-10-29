/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:57:22 by witong            #+#    #+#             */
/*   Updated: 2024/10/02 09:25:35 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	ft_wordcount(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			count++;
		s++;
	}
	return (count);
}

static char	*ft_strndup(const char *s, size_t len)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = s[i];
		i++;
	}
	dest[len] = '\0';
	return (dest);
}

static char	**ft_free_error(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static char	**split_words(char **array, char const *s, char c)
{
	int		wc;
	int		i;

	wc = 0;
	while (*s)
	{
		if (*s != c)
		{
			i = 0;
			while (s[i] && s[i] != c)
				i++;
			array[wc] = ft_strndup(s, i);
			if (!array[wc])
				return (ft_free_error(array));
			wc++;
			s += i;
		}
		else
			s++;
	}
	array[wc] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		total_words;

	if (s == NULL)
		return (NULL);
	total_words = ft_wordcount(s, c);
	array = (char **)malloc(sizeof(char *) * (total_words + 1));
	if (!array)
		return (NULL);
	array = split_words(array, s, c);
	return (array);
}
