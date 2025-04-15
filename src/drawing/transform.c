/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:10:12 by hganet            #+#    #+#             */
/*   Updated: 2025/04/15 11:45:02 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Projects a 3D point into 2D screen space using isometric projection.
 *
 * This function applies three main steps:
 * 1. Scales the point based on zoom level (fdf->scale)
 * 2. Recenters it around the origin using map width/height
 * 3. Applies isometric projection to simulate 3D on a 2D plane
 * 4. Offsets the result to center the map on screen
 *
 * @param p    A 3D point (with x, y, z) from the map grid.
 * @param fdf  Pointer to the FDF context (contains scale, offsets, etc.).
 * @return     A projected t_point with new screen-space x and y.
 */
t_point	project_point(t_point p, t_fdf *fdf)
{
	t_point	result;
	float	x;
	float	y;
	float	z;

	x = (p.x - fdf->columns / 2.0f) * fdf->scale;
	y = (p.y - fdf->rows / 2.0f) * fdf->scale;
	z = p.z * fdf->scale * fdf->z_scale;
	result.x = (x - y) * cos(0.523599);
	result.y = (x + y) * sin(0.523599) - z;
	result.x += fdf->x_offset;
	result.y += fdf->y_offset;
	return (result);
}

/**
 * @brief Initializes scale and offset to fit the map nicely inside the window.
 *
 * This computes an adaptive zoom level depending on the map size,
 * and sets offsets to center it.
 *
 * @param fdf Pointer to the FDF structure containing map size info.
 */
void	init_transform(t_fdf *fdf)
{
	float	x_scale;
	float	y_scale;

	x_scale = (float)(WIN_WIDTH / 1.5f) / fdf->columns;
	y_scale = (float)(WIN_HEIGHT / 1.5f) / fdf->rows;
	fdf->scale = fmin(x_scale, y_scale);
	fdf->x_offset = WIN_WIDTH / 2;
	fdf->y_offset = WIN_HEIGHT / 2;
	fdf->z_scale = 0.15f;
}
