/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugoganet <hugoganet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:11:55 by hugoganet         #+#    #+#             */
/*   Updated: 2025/03/03 12:51:46 by hugoganet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief Puts a pixel into the image buffer instead of the window directly.
 *
 * @param img Pointer to the image structure.
 * @param x X-coordinate of the pixel.
 * @param y Y-coordinate of the pixel.
 * @param color Color of the pixel in hexadecimal (e.g., 0xFFFFFF for white).
 */
void put_pixel_to_image(t_img *img, int x, int y, int color)
{
	char *dst;

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

/**
 * @brief Draws a line between two points using Bresenham's algorithm.
 *
 * @param fdf Pointer to the FDF structure containing the MiniLibX context.
 * @param p1 First point (starting point of the line).
 * @param p2 Second point (ending point of the line).
 * @param color Color of the line in hexadecimal.
 */
void draw_line(t_fdf *fdf, t_point p1, t_point p2, int color)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;

	dx = abs(p2.x - p1.x);
	dy = abs(p2.y - p1.y);
	sx = (p1.x < p2.x) ? 1 : -1;
	sy = (p1.y < p2.y) ? 1 : -1;
	err = dx - dy;
	while (p1.x != p2.x || p1.y != p2.y)
	{
		put_pixel_to_image(&fdf->img, p1.x, p1.y, color);
		if (2 * err > -dy)
		{
			err -= dy;
			p1.x += sx;
		}
		if (2 * err < dx)
		{
			err += dx;
			p1.y += sy;
		}
	}
}

/**
 * @brief Draws the entire wireframe map by connecting adjacent points.
 *
 * @param fdf Pointer to the FDF structure containing the map and rendering context.
 */
void draw_map(t_fdf *fdf)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < fdf->rows)
	{
		x = 0;
		while (x < fdf->columns)
		{
			if (x < fdf->columns - 1) /* Draw line to the right */
				draw_line(fdf, fdf->map[y][x], fdf->map[y][x + 1], 0xFFFFFF);
			if (y < fdf->rows - 1) /* Draw line downward */
				draw_line(fdf, fdf->map[y][x], fdf->map[y + 1][x], 0xFFFFFF);
			x++;
		}
		y++;
	}
}

/**
 * @brief Renders the image buffer to the MiniLibX window.
 *
 * @param fdf Pointer to the FDF structure containing the rendering context.
 */
void render_image(t_fdf *fdf)
{
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
							fdf->img.img_ptr, 0, 0);
}
