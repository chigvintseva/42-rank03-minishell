/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:44:12 by achigvin          #+#    #+#             */
/*   Updated: 2025/05/15 17:44:13 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s_dest;
	unsigned char	*s_src;

	if (n > 0 && !dest && !src)
		return (NULL);
	s_dest = (unsigned char *)dest;
	s_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		s_dest[i] = s_src[i];
		i++;
	}
	return (dest);
}
