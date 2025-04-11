/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:11:55 by hugoganet         #+#    #+#             */
/*   Updated: 2025/04/11 15:21:54 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <mlx.h>
#include <stdlib.h>
#include <math.h>


/**
 * @brief Applies scaling and translation to a 3D point before drawing.
 *
 * This includes zooming (based on map size), centering, and projecting to 2D.
 *
 * @param p The original 3D point.
 * @param fdf Pointer to the FDF structure for access to scale and offset.
 * @return The final screen-space 2D point ready for drawing.
 */
t_point project_point(t_point p, t_fdf *fdf)
{
	t_point result;

	// Center the map in logical space (pre-projection)
	float x = (p.x - fdf->columns / 2.0f) * fdf->scale;
	float y = (p.y - fdf->rows / 2.0f) * fdf->scale;
	float z = p.z * fdf->scale * fdf->z_scale;

	// Apply isometric projection
	result.x = (x - y) * cos(0.523599); // 30 degrees
	result.y = (x + y) * sin(0.523599) - z;

	// Move to center of screen
	result.x += fdf->x_offset;
	result.y += fdf->y_offset;

	return result;
}

/**
 * @brief Initializes scale and offset to fit the map nicely inside the window.
 *
 * This computes an adaptive zoom level depending on the map size,
 * and sets offsets to center it.
 *
 * @param fdf Pointer to the FDF structure containing map size info.
 */
void init_transform(t_fdf *fdf)
{
	float x_scale;
	float y_scale;

	// Scale so map fits inside half of window
	x_scale = (float)(WIN_WIDTH / 1.5f) / fdf->columns;
	y_scale = (float)(WIN_HEIGHT / 1.5f) / fdf->rows;
	fdf->scale = fmin(x_scale, y_scale);

	// Center map around its middle point
	fdf->x_offset = WIN_WIDTH / 2;
	fdf->y_offset = WIN_HEIGHT / 2;
}

/**
 * @brief Initializes the MiniLibX image structure used for drawing.
 *
 * Creates an off-screen image buffer and links it to the fdf->img structure.
 * This image will be drawn to the window after being filled with pixels.
 *
 * @param fdf Pointer to the FDF structure.
 */
void init_image(t_fdf *fdf)
{
	fdf->img.img_ptr = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img.img_ptr)
	{
		ft_printf("Error: Failed to create an image.\n");
		exit(1);
	}
	fdf->img.addr = mlx_get_data_addr(fdf->img.img_ptr,
									  &fdf->img.bits_per_pixel, &fdf->img.line_length, &fdf->img.endian);
	fdf->img.width = WIN_WIDTH;
	fdf->img.height = WIN_HEIGHT;
}

/**
 * @brief Draws a pixel in the image buffer if it's within screen bounds.
 *
 * This writes directly to the image's memory, not to the screen itself.
 *
 * @param img Pointer to the image structure.
 * @param x Pixel X-coordinate.
 * @param y Pixel Y-coordinate.
 * @param color Pixel color in hex format (e.g., 0xFFFFFF for white).
 */
void put_pixel_to_image(t_img *img, int x, int y, int color)
{
	char *dst;

	if (!img || !img->addr)
		return;
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/**
 * @brief Draws a line between two points using Bresenham's algorithm.
 *
 * Calculates the points on a line by incrementing step-by-step
 * using only integers for performance.
 *
 * @param fdf Pointer to the FDF structure.
 * @param p1 Starting screen-space point.
 * @param p2 Ending screen-space point.
 * @param color Line color.
 */
void draw_line(t_fdf *fdf, t_point p1, t_point p2, int color)
{
	int delta[2];
	int step[2];
	int err;
	int e2;

	delta[0] = abs(p2.x - p1.x);
	delta[1] = abs(p2.y - p1.y);
	step[0] = (p1.x < p2.x) ? 1 : -1;
	step[1] = (p1.y < p2.y) ? 1 : -1;
	err = delta[0] - delta[1];
	while (p1.x != p2.x || p1.y != p2.y)
	{
		put_pixel_to_image(&fdf->img, p1.x, p1.y, color);
		e2 = err * 2;
		if (e2 > -delta[1])
		{
			err -= delta[1];
			p1.x += step[0];
		}
		if (e2 < delta[0])
		{
			err += delta[0];
			p1.y += step[1];
		}
	}
}

/**
 * @brief Draws the entire wireframe by connecting neighboring points.
 *
 * This loops through all points in the map and connects them to the
 * point to their right and the point below them.
 *
 * @param fdf Pointer to the FDF structure containing the map and config.
 */
void draw_map(t_fdf *fdf)
{
	int x;
	int y;
	int color;
	t_point p1;
	t_point p2;

	y = 0;
	while (y < fdf->rows)
	{
		x = 0;
		while (x < fdf->columns)
		{
			p1 = fdf->map[y][x];

			if (x < fdf->columns - 1)
			{
				p2 = fdf->map[y][x + 1];
				color = get_color((p1.z + p2.z) / 2, fdf->min_z, fdf->max_z);
				draw_line(fdf, project_point(p1, fdf), project_point(p2, fdf), color);
			}

			if (y < fdf->rows - 1)
			{
				p2 = fdf->map[y + 1][x];
				color = get_color((p1.z + p2.z) / 2, fdf->min_z, fdf->max_z);
				draw_line(fdf, project_point(p1, fdf), project_point(p2, fdf), color);
			}

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
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
							fdf->img.img_ptr, 0, 0);
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
