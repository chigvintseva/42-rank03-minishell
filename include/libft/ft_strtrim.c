/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:47:11 by achigvin          #+#    #+#             */
/*   Updated: 2025/05/15 17:47:12 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_inset(char const *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static	int	ft_onlyset(char const *s1, char const *set)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s1[i] != '\0')
	{
		if (ft_inset(set, s1[i]) == 0)
			count++;
		i++;
	}
	if (count == 0)
		return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*str;
	size_t	i;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	if (ft_onlyset(s1, set) == 1)
		return (ft_strdup(""));
	start = 0;
	end = ft_strlen(s1) - 1;
	while ((s1[start + 1] != '\0') && ft_inset(set, s1[start]))
		start++;
	while ((end > 0) && ft_inset(set, s1[end]))
		end--;
	str = (char *)malloc(end - start + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (start <= end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
