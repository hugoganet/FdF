/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugoganet <hugoganet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:54:27 by hugoganet         #+#    #+#             */
/*   Updated: 2025/03/25 08:05:23 by hugoganet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <mlx.h>

/**
 * @brief Initializes the MiniLibX image structure.
 *
 * @param fdf Pointer to the FDF structure.
 */
void init_image(t_fdf *fdf)
{
	// Create a new image buffer (800x600 pixels)
	fdf->img.img_ptr = mlx_new_image(fdf->mlx_ptr, 800, 600);
	if (!fdf->img.img_ptr)
	{
		ft_printf("Error: Failed to create an image.\n");
		exit(1);
	}

	// Get access to the image buffer's data
	fdf->img.addr = mlx_get_data_addr(fdf->img.img_ptr,
									  &fdf->img.bits_per_pixel, &fdf->img.line_length, &fdf->img.endian);

	// Set image dimensions
	fdf->img.width = 800;
	fdf->img.height = 600;
}

/**
 * @brief Entry point of the FDF program.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return int Returns 0 on success, 1 on error.
 */
int main(int argc, char **argv)
{
	t_fdf fdf;

	// Check if the user provided a valid file
	if (argc != 2)
	{
		ft_printf("Usage: %s <map.fdf>\n", argv[0]);
		return (1);
	}

	// Parse the map file into a 2D array
	fdf.map = parse_map(argv[1], &fdf.rows, &fdf.columns);
	if (!fdf.map)
	{
		ft_printf("Error: Failed to parse the map.\n");
		return (1);
	}

	// Initialize MiniLibX (required for graphics)
	fdf.mlx_ptr = mlx_init();
	if (!fdf.mlx_ptr)
		return (1);

	// Create a new MiniLibX window (800x600 pixels)
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, 800, 600, "FdF");

	// 1️⃣ Initialize the image buffer before drawing
	init_image(&fdf);

	// 2️⃣ Draw the map into the image buffer
	draw_map(&fdf);

	// 3️⃣ Render the image to the window
	render_image(&fdf);

	// 4️⃣ Start the MiniLibX event loop (keeps the window open)
	mlx_loop(fdf.mlx_ptr);

	return (0);
}
