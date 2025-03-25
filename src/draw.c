/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugoganet <hugoganet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:11:55 by hugoganet         #+#    #+#             */
/*   Updated: 2025/03/10 12:32:23 by hugoganet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief Places a pixel at a specific (x, y) coordinate inside the image buffer.
 *
 * Instead of directly drawing on the screen, we modify the image stored in memory.
 * This allows smoother rendering by updating the whole image at once.
 *
 * @param img Pointer to the image structure.
 * @param x X-coordinate of the pixel.
 * @param y Y-coordinate of the pixel.
 * @param color Color of the pixel in hexadecimal format (e.g., 0xFFFFFF for white).
 */
void put_pixel_to_image(t_img *img, int x, int y, int color)
{
	char *dst;

	// Check if image is properly initialized
	if (!img || !img->addr)
	{
		ft_printf("Error: Image is not initialized.\n");
		return;
	}

	// Check if pixel is inside valid boundaries
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
	{
		ft_printf("Warning: Trying to draw out of bounds (x=%d, y=%d)\n", x, y);
		return;
	}

	// Compute the pixel's memory address
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));

	// Cast the pointer 'dst' to a pointer of type 'unsigned int'
	// Dereference the casted pointer to access the memory location it points to
	// Assign the value of 'color' to the memory location pointed to by the casted pointer
	*(unsigned int *)dst = color;
}

/**
 * @brief Draws a line between two points using Bresenham's line algorithm.
 *
 * Bresenham's algorithm efficiently calculates which pixels should be filled
 * to create a visually continuous line. Instead of using floating-point math,
 * it works with integer increments and error correction.
 *
 * @param fdf Pointer to the FDF structure containing the MiniLibX context.
 * @param p1 Starting point of the line.
 * @param p2 Ending point of the line.
 * @param color Color of the line in hexadecimal format.
 */
void draw_line(t_fdf *fdf, t_point p1, t_point p2, int color)
{
	int delta[2]; // delta[0] = dx (horizontal difference), delta[1] = dy (vertical difference)
	int step[2];  // step[0] = x direction (+1 or -1), step[1] = y direction (+1 or -1)
	int err;	  // Error accumulator to determine when to step in the y direction
	int e2;

	// Calculate absolute differences in x and y
	delta[0] = abs(p2.x - p1.x);
	delta[1] = abs(p2.y - p1.y);

	// Determine the direction of movement (left/right, up/down)
	step[0] = (p1.x < p2.x) ? 1 : -1;
	step[1] = (p1.y < p2.y) ? 1 : -1;

	// Initialize error value
	err = delta[0] - delta[1];

	// Draw the line point by point
	while (p1.x != p2.x || p1.y != p2.y)
	{
		// Place a pixel at the current point
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
 * @brief Draws the entire wireframe map by connecting adjacent points.
 *
 * This function loops through all points in the map and connects them
 * horizontally and vertically with lines. This forms the "wireframe" model.
 *
 * @param fdf Pointer to the FDF structure containing the map and rendering context.
 */
void draw_map(t_fdf *fdf)
{
	int x;
	int y;

	// Iterate over each row in the map
	y = 0;
	while (y < fdf->rows)
	{
		// Iterate over each column in the row
		x = 0;
		while (x < fdf->columns)
		{
			// Draw a line to the right (if not at the last column)
			if (x < fdf->columns - 1)
				draw_line(fdf, fdf->map[y][x], fdf->map[y][x + 1], 0xFFFFFF);

			// Draw a line downward (if not at the last row)
			if (y < fdf->rows - 1)
				draw_line(fdf, fdf->map[y][x], fdf->map[y + 1][x], 0xFFFFFF);
			// Move to the next column
			x++;
		}
		// Move to the next row
		y++;
	}
}

/**
 * @brief Renders the image buffer to the MiniLibX window.
 *
 * The drawing functions only modify an off-screen image buffer.
 * This function transfers the image to the window for display.
 *
 * @param fdf Pointer to the FDF structure containing the rendering context.
 */
void render_image(t_fdf *fdf)
{
	// Clear the window before updating the new image
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);

	// Put the updated image buffer onto the screen
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img.img_ptr, 0, 0);
}

/**
 * @brief Draws the map and updates the window with the new image.
 *
 * This function acts as the "main render function." It ensures the map
 * is drawn to the image buffer, then displayed on the window.
 *
 * @param fdf Pointer to the FDF structure containing the rendering context.
 */
void update_window(t_fdf *fdf)
{
	// Draw the wireframe map into the image buffer
	draw_map(fdf);

	// Push the updated image to the window
	render_image(fdf);
}
