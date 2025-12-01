/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:43:07 by achigvin          #+#    #+#             */
/*   Updated: 2025/05/15 17:43:09 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr_memory;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (size > SIZE_MAX / nmemb)
		return (NULL);
	ptr_memory = (void *)malloc(nmemb * size);
	if (!ptr_memory)
		return (NULL);
	ft_bzero(ptr_memory, nmemb * size);
	return (ptr_memory);
}
