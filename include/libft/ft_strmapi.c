/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:34:19 by achigvin          #+#    #+#             */
/*   Updated: 2025/05/22 13:34:20 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_str;
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	new_str = (char *)malloc(len + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		new_str[i] = f((unsigned int)i, s[i]);
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
