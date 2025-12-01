/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:46:46 by achigvin          #+#    #+#             */
/*   Updated: 2025/05/15 17:46:47 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	chars_left;

	i = 0;
	if (s2[i] == '\0')
		return ((char *)s1);
	while ((i < n) && (s1[i] != '\0'))
	{
		j = 0;
		chars_left = n - i;
		while ((s1[i + j] == s2[j]) && (chars_left > 0)
			&& (s2[j] != '\0') && (s1[i + j] != '\0'))
		{
			j++;
			chars_left--;
		}
		if (s2[j] == '\0')
			return ((char *)&s1[i]);
		i++;
	}
	return (NULL);
}
