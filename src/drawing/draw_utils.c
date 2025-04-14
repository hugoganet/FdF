/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:04:56 by hganet            #+#    #+#             */
/*   Updated: 2025/04/14 16:01:02 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Draws a pixel in the off-screen image buffer if it's within bounds.
 *
 * This function directly accesses the raw memory of the image buffer and writes
 * the given color at pixel (x, y). This is *not* immediate screen drawing — the
 * pixel will be visible only after calling mlx_put_image_to_window().
 *
 * @param img   Pointer to the t_img structure (holds image buffer metadata).
 * @param x     X-coordinate of the pixel (in pixels).
 * @param y     Y-coordinate of the pixel (in pixels).
 * @param color Color in hexadecimal (e.g., 0xFFFFFF for white).
 */
void put_pixel_to_image(t_img *img, int x, int y, int color)
{
	char *dst;

	if (!img || !img->addr)
		return;
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return;

	/**
	 * Calculate the memory address of the pixel:
	 *
	 * img->bits_per_pixel = 32 → 4 bytes per pixel
	 * img->line_length = 1000 → 1000 bytes per row (250 pixels if 32 bpp)
	 * You want to draw at (10, 3)
	 * y * line_length = 3 * 1000 = 3000 bytes (start of row 3)
	 * x * 4 = 10 * 4 = 40 bytes (10 pixels across)
	 * → dst = img->addr + 3040
	 * This is the address of the pixel at (10, 3)
	 */
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));

	// Write the color value (as an unsigned int) into the pixel's memory
	*(unsigned int *)dst = color;
}

/**
 * @brief Draws a horizontal line between two points in the map.
 * 		  This function connects the current point to the point to its right.
 *
 * @param fdf Pointer to the FDF structure.
 * @param x X-coordinate of the point.
 * @param y Y-coordinate of the point.
 */
void draw_horizontal_line(t_fdf *fdf, int x, int y)
{
	t_point p1;
	t_point p2;
	int color;

	// Check if the point is not on the last column
	// If it is, we can't draw a line to the right
	if (x < fdf->columns - 1)
	{
		// Get the two points to draw the line between
		// p1 is the current point
		// p2 is the point to the right
		p1 = fdf->map[y][x];
		p2 = fdf->map[y][x + 1];
		// Get the color based on the average z value of the two points
		color = get_color((p1.z + p2.z) / 2, fdf->min_z, fdf->max_z);
		// Draw the line between the two points
		draw_line(fdf, project_point(p1, fdf), project_point(p2, fdf), color);
	}
}

/**
 * @brief Draws a vertical line between two points in the map.
 * 		  This function connects the current point to the point below it.
 *
 * @param fdf Pointer to the FDF structure.
 * @param x X-coordinate of the point.
 * @param y Y-coordinate of the point.
 */
void draw_vertical_line(t_fdf *fdf, int x, int y)
{
	t_point p1;
	t_point p2;
	int color;

	// Check if the point is not on the last row
	// If it is, we can't draw a line below
	if (y < fdf->rows - 1)
	{
		p1 = fdf->map[y][x];
		p2 = fdf->map[y + 1][x];
		color = get_color((p1.z + p2.z) / 2, fdf->min_z, fdf->max_z);
		draw_line(fdf, project_point(p1, fdf), project_point(p2, fdf), color);
	}
}