/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:07:15 by hganet            #+#    #+#             */
/*   Updated: 2025/04/21 14:42:10 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char *s2, size_t size);
char	*ft_strjoin_gnl(char *s1, char *s2, size_t size);
char	*read_and_store(int fd, char *buffered_data);
char	*extract_line(char *buffered_data);
char	*update_buffer(char *buffered_data);
void	flush_gnl(void);

#endif