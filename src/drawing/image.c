/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:11:22 by hganet            #+#    #+#             */
/*   Updated: 2025/04/14 14:11:43 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	/**
	 * Create a new image in memory (not shown on screen yet).
	 * - mlx_ptr: your MLX session (must already be initialized)
	 * - WIN_WIDTH & WIN_HEIGHT: size of the image in pixels
	 * - Returns: a pointer to the image buffer (img_ptr)
	 */
	fdf->img.img_ptr = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img.img_ptr)
	{
		ft_printf("Error: Failed to create an image.\n");
		exit(1);
	}
	/**
	 * Get the address of the image's pixel data in memory.
	 * This is how we’ll actually modify the pixels manually.
	 *
	 * Also retrieves image format metadata:
	 * - bits_per_pixel: usually 32 (8 bits for R, G, B, and Alpha)
	 * - line_length: number of bytes per row (may be more than width * 4)
	 * - endian: 0 for little-endian, 1 for big-endian
	 *
	 * addr = pointer to the raw pixel array.
	 */
	fdf->img.addr = mlx_get_data_addr(
		fdf->img.img_ptr,
		&fdf->img.bits_per_pixel,
		&fdf->img.line_length,
		&fdf->img.endian);
	// Store the image dimensions (used for bounds checking or rendering logic)
	fdf->img.width = WIN_WIDTH;
	fdf->img.height = WIN_HEIGHT;
}