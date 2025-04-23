/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:10:44 by hganet            #+#    #+#             */
/*   Updated: 2025/04/21 14:50:10 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static char	**get_static_buffer(void)
{
	static char	*buffered_data = NULL;

	return (&buffered_data);
}

char	*get_next_line(int fd)
{
	char	**buf_ptr;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf_ptr = get_static_buffer();
	*buf_ptr = read_and_store(fd, *buf_ptr);
	if (!*buf_ptr)
		return (NULL);
	line = extract_line(*buf_ptr);
	*buf_ptr = update_buffer(*buf_ptr);
	if (!line)
	{
		free(*buf_ptr);
		*buf_ptr = NULL;
	}
	return (line);
}

void	flush_gnl(void)
{
	char	**buf_ptr;

	buf_ptr = get_static_buffer();
	if (*buf_ptr)
	{
		free(*buf_ptr);
		*buf_ptr = NULL;
	}
}
