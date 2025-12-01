/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:44:23 by achigvin          #+#    #+#             */
/*   Updated: 2025/05/22 13:35:28 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*s_dest;
	const unsigned char	*s_src;

	if (n == 0 || src == dest)
		return (dest);
	s_dest = (unsigned char *)dest;
	s_src = (const unsigned char *)src;
	if (src < dest)
	{
		i = n - 1;
		while (i > 0)
		{
			s_dest[i] = s_src[i];
			i--;
		}
		s_dest[i] = s_src[i];
	}
	else
		return (ft_memcpy(dest, src, n));
	return (dest);
}
