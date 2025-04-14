/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:54:27 by hugoganet         #+#    #+#             */
/*   Updated: 2025/04/14 16:18:04 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <mlx.h>


/**
 * @brief Entry point of the FDF program.
 *
 * The program reads a .fdf file, parses its content, initializes the
 * graphics system, applies a 3D projection to all points, and renders
 * the result inside a graphical window using MiniLibX.
 *
 * @param argc Number of arguments passed to the program.
 * @param argv Argument vector (expects one .fdf filename).
 * @return int Returns 0 on success, or 1 on error.
 */
int main(int argc, char **argv)
{
	// declare the structure representing the FDF application
	t_fdf fdf;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map.fdf>\n", argv[0]);
		return (1);
	}
	/**
	 * Parse the map from the provided file.
	 * After this step, fdf.map is a 2D array of points.
	 * We store fdf->min_z and fdf->max_z to use them in color gradient.
	 */
	fdf.map = parse_map(argv[1], &fdf);
	// check if the map was parsed successfully
	if (!fdf.map)
	{
		ft_printf("Error: Failed to parse the map.\n");
		return (1);
	}
	// Initialize the MiniLibX (MLX) graphics system and store the pointer that represents the MLX session/context.
	fdf.mlx_ptr = mlx_init();
	// If the initialization fails, free mallocs and exit
	if (!fdf.mlx_ptr)
		cleanup_and_exit(&fdf, 1);
	// Create a new window with the specified width, height, and title. And store the pointer to the window in fdf.win_ptr.
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (!fdf.mlx_ptr)
		cleanup_and_exit(&fdf, 1);
	// Initialize the image buffer used for drawing.
	init_image(&fdf);
	// Choose the right zoom level(scale) and center(offset) the map in the window.
	init_transform(&fdf);
	// Draw the wireframe map by connecting neighboring points.
	update_window(&fdf);
	// Set up event handlers for keyboard input (ESC)
	mlx_key_hook(fdf.win_ptr, handle_key, &fdf);
	// Set up event handlers for window close button (red cross)
	mlx_hook(fdf.win_ptr, 17, 0, handle_close, &fdf);
	// Enter the main event loop of the MiniLibX, which will keep the window open and responsive to events.
	mlx_loop(fdf.mlx_ptr);
	return (0);
}
