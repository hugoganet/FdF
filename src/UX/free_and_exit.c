/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugoganet <hugoganet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:49:58 by hganet            #+#    #+#             */
/*   Updated: 2025/04/23 17:17:12 by hugoganet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"

/**
 * @brief Frees the map rows up to a specified index.
 * @param map The 2D array of points.
 * @param up_to The number of rows to free.
 */
void	free_map_rows(t_point **map, int up_to)
{
	int	i;

	i = 0;
	while (i < up_to)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

/**
 * @brief Cleans up the FDF context and exits the program.
 * @param fdf The FDF context.
 * @param exit_code The exit code to return.
 */
void	cleanup_and_exit(t_fdf *fdf, int exit_code, const char *msg)
{
	if (fdf->map)
		free_map_rows(fdf->map, fdf->rows);
	if (fdf->img.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->img.img_ptr);
	if (fdf->win_ptr)
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	if (fdf->mlx_ptr)
		free(fdf->mlx_ptr);
	flush_gnl();
	ft_printf("%s\n", msg);
	exit(exit_code);
}

/**
 * @brief Frees a NULL-terminated array of strings.
 */
void	free_split_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}
