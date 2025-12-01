/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:45:15 by achigvin          #+#    #+#             */
/*   Updated: 2025/05/22 14:44:31 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_parts(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while ((s[i] != c) && (s[i] != '\0'))
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	*ft_addword(const char *s, char c)
{
	char	*word;
	size_t	i;

	i = 0;
	while ((s[i] != '\0') && (s[i] != c))
		i++;
	word = (char *)malloc(i + 1);
	if (!word)
		return (NULL);
	i = 0;
	while ((s[i] != '\0') && (s[i] != c))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**ft_free_return(char **strs, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	j;
	size_t	parts;

	if (!s)
		return (NULL);
	parts = ft_parts(s, c);
	strs = (char **)malloc(sizeof(char *) * (parts + 1));
	if (!strs)
		return (NULL);
	j = 0;
	while (j < parts)
	{
		while (*s && *s == c)
			s++;
		strs[j++] = ft_addword(&(*s), c);
		if (strs[j - 1] == NULL)
			return (ft_free_return(strs, j - 1));
		while (*s && *s != c)
			s++;
	}
	strs[j] = NULL;
	return (strs);
}
