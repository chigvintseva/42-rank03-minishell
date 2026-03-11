/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:46:58 by achigvin          #+#    #+#             */
/*   Updated: 2025/05/15 17:46:59 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	chr;
	size_t			len;

	len = ft_strlen(s);
	chr = (unsigned char)c;
	while (len != 0 && (s[len] != chr))
		len--;
	if (s[len] == chr)
		return ((char *)(&(s[len])));
	return (NULL);
}
