/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugoganet <hugoganet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:04:56 by hganet            #+#    #+#             */
/*   Updated: 2025/04/16 09:38:21 by hugoganet        ###   ########.fr       */
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
void	put_pixel_to_image(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->addr)
		return ;
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + ((y * img->line_length )+ x * (img->bits_per_pixel / 8));
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
void	draw_horizontal_line(t_fdf *fdf, int x, int y)
{
	t_point	p1;
	t_point	p2;
	int		color;

	if (x < fdf->columns - 1)
	{
		p1 = fdf->map[y][x];
		p2 = fdf->map[y][x + 1];
		if (p1.color != -1 && p2.color != -1)
			color = interpolate_color(p1.color, p2.color, 0.5f);
		else
			color = get_color((p1.z + p2.z) / 2, fdf->min_z, fdf->max_z);
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
void	draw_vertical_line(t_fdf *fdf, int x, int y)
{
	t_point	p1;
	t_point	p2;
	int		color;

	if (y < fdf->rows - 1)
	{
		p1 = fdf->map[y][x];
		p2 = fdf->map[y + 1][x];
		if (p1.color != -1 && p2.color != -1)
			color = interpolate_color(p1.color, p2.color, 0.5f);
		else
			color = get_color((p1.z + p2.z) / 2, fdf->min_z, fdf->max_z);
		draw_line(fdf, project_point(p1, fdf), project_point(p2, fdf), color);
	}
}
