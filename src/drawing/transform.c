/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:10:12 by hganet            #+#    #+#             */
/*   Updated: 2025/04/14 15:40:54 by hganet           ###   ########.fr       */
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
t_point project_point(t_point p, t_fdf *fdf)
{
	t_point result;
	float x;
	float y;
	float z;

	// Step 1: Center the point relative to the map’s midpoint, then scale it
	x = (p.x - fdf->columns / 2.0f) * fdf->scale;
	y = (p.y - fdf->rows / 2.0f) * fdf->scale;

	// Step 2: Scale the height (z) with z_scale (height exaggeration)
	z = p.z * fdf->scale * fdf->z_scale;

	// Step 3: Apply isometric projection (rotate x/y, subtract z)
	// Angle used: 30 degrees → cos(30°) = 0.866, sin(30°) = 0.5
	result.x = (x - y) * cos(0.523599);
	result.y = (x + y) * sin(0.523599) - z;

	// Step 4: Move the point into screen center
	result.x += fdf->x_offset; // horizontal pixel coordinate on screen
	result.y += fdf->y_offset; // vertical pixel coordinate on screen

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
void init_transform(t_fdf *fdf)
{
	float x_scale;
	float y_scale;

	// WIN_WIDTH / 1.5f / fdf->columns = Divide th 2/3 of the window width by number of columns
	// x_scale becomes the maximum pixel width per column you can use
	x_scale = (float)(WIN_WIDTH / 1.5f) / fdf->columns;
	// WIN_HEIGHT / 1.5f / fdf->rows = Divide th 2/3 of the window height by number of rows
	y_scale = (float)(WIN_HEIGHT / 1.5f) / fdf->rows;
	// Determine the minimum of the two scales to maintain aspect ratio
	fdf->scale = fmin(x_scale, y_scale);
	// Set the x_offset and y_offset to center the map in the window
	fdf->x_offset = WIN_WIDTH / 2;
	fdf->y_offset = WIN_HEIGHT / 2;
	// Set the z_scale to a default value
	fdf->z_scale = 0.15f;
}
