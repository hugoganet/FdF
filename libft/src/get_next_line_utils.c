/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:55:00 by hganet            #+#    #+#             */
/*   Updated: 2025/04/21 14:49:07 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2, size_t size)
{
	char	*result_str;
	size_t	s1_len;
	size_t	i;
	size_t	j;

	s1_len = ft_strlen(s1);
	result_str = (char *)ft_calloc((s1_len + size + 1), sizeof(char));
	if (!result_str)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		result_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && j < size)
		result_str[i++] = s2[j++];
	free(s1);
	return (result_str);
}

char	*read_and_store(int fd, char *buffered_data)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(buffered_data, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		if (bytes_read > 0)
			buffered_data = ft_strjoin_gnl(buffered_data, buffer, bytes_read);
	}
	free(buffer);
	return (buffered_data);
}

char	*extract_line(char *buffered_data)
{
	char	*line;
	size_t	i;

	if (!buffered_data || !*buffered_data)
		return (NULL);
	i = 0;
	while (buffered_data[i] && buffered_data[i] != '\n')
		i++;
	line = (char *)ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffered_data[i] && buffered_data[i] != '\n')
	{
		line[i] = buffered_data[i];
		i++;
	}
	if (buffered_data[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*update_buffer(char *buffered_data)
{
	size_t	i;
	size_t	j;
	char	*new_buffer;

	i = 0;
	while (buffered_data[i] && buffered_data[i] != '\n')
		i++;
	if (!buffered_data[i])
		return (free(buffered_data), NULL);
	new_buffer = (char *)ft_calloc(
			ft_strlen(buffered_data) - i + 1, sizeof(char));
	if (!new_buffer)
		return (free(buffered_data), NULL);
	i++;
	j = 0;
	while (buffered_data[i])
		new_buffer[j++] = buffered_data[i++];
	free(buffered_data);
	return (new_buffer);
}
