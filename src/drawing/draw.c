/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:11:55 by hugoganet         #+#    #+#             */
/*   Updated: 2025/04/14 16:08:13 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


/**
 * @brief Draws the entire wireframe by connecting neighboring points.
 *
 * This loops through all points in the map and connects them to the
 * point to their right and the point below them.
 *
 * @param fdf Pointer to the FDF structure containing the map and config.
 */
void	draw_map(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	// Iterate through each row of the map
	while (y < fdf->rows)
	{
		x = 0;
		// Iterate through each column of the current row
		while (x < fdf->columns)
		{
			// Draw a line to the right if not at the last column
			draw_horizontal_line(fdf, x, y);
			// Draw a line downwards if not at the last row
			draw_vertical_line(fdf, x, y);
			x++;
		}
		y++;
	}
}

/**
 * @brief Pushes the image buffer to the MiniLibX window.
 *
 * Must be called after all drawing is done.
 *
 * @param fdf Pointer to the FDF structure.
 */
void render_image(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	mlx_put_image_to_window(
							fdf->mlx_ptr,
							fdf->win_ptr,
							fdf->img.img_ptr,
							0,
							0);
}

/**
 * @brief Main rendering function to draw and display the map.
 *
 * Combines draw_map() and render_image() to update the screen.
 *
 * @param fdf Pointer to the FDF structure.
 */
void update_window(t_fdf *fdf)
{
	draw_map(fdf);
	render_image(fdf);
}
