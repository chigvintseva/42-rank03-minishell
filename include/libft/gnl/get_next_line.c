/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achigvin <achigvin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:27:02 by achigvin          #+#    #+#             */
/*   Updated: 2025/07/24 18:33:29 by achigvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_update_buffer(char *buffer)
{
	char	*temp_buffer;
	size_t	i;
	size_t	k;

	if (!buffer)
		return (NULL);
	i = 0;
	temp_buffer = NULL;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
		return (free(buffer), NULL);
	temp_buffer = (char *)malloc((ft_strlen(buffer + i)) + 1);
	if (!temp_buffer)
		return (free(buffer), NULL);
	k = 0;
	i++;
	while (buffer[i] != '\0')
		temp_buffer[k++] = buffer[i++];
	temp_buffer[k] = '\0';
	free(buffer);
	buffer = temp_buffer;
	return (buffer);
}

char	*ft_extract_line(char *buffer)
{
	char	*next_line;
	size_t	i;
	size_t	k;

	if (!buffer)
		return (NULL);
	i = 0;
	k = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	next_line = (char *)malloc(sizeof(char) * i + 1);
	if (!next_line)
		return (NULL);
	while (k < i)
	{
		next_line[k] = buffer[k];
		k++;
	}
	next_line[k] = '\0';
	return (next_line);
}

char	*ft_read(int fd, char *buffer)
{
	char	*chunk;
	char	*temp_buffer;
	int		read_bytes;

	chunk = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!chunk)
		return (free(buffer), NULL);
	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, chunk, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free(chunk), free(buffer), NULL);
		chunk[read_bytes] = '\0';
		if (!buffer)
			buffer = ft_strdup("");
		temp_buffer = ft_strjoin(buffer, chunk);
		if (!temp_buffer)
			return (free(chunk), free(buffer), NULL);
		free(buffer);
		buffer = temp_buffer;
		if (ft_strchr(chunk, (int) '\n') != NULL)
			break ;
	}
	return (free(chunk), buffer);
}

char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(buffer), buffer = NULL, NULL);
	if (!buffer)
		buffer = ft_strdup("");
	buffer = ft_read(fd, buffer);
	if (!buffer)
		return (NULL);
	if (buffer[0] == '\0')
		return (free(buffer), buffer = NULL, NULL);
	next_line = NULL;
	next_line = ft_extract_line(buffer);
	if (!next_line)
		return (buffer = NULL, NULL);
	buffer = ft_update_buffer(buffer);
	return (next_line);
}
