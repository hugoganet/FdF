/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:54:27 by hugoganet         #+#    #+#             */
/*   Updated: 2025/04/11 15:14:18 by hganet           ###   ########.fr       */
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
	t_fdf fdf;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map.fdf>\n", argv[0]);
		return (1);
	}
	fdf.map = parse_map(argv[1], &fdf);
	if (!fdf.map)
	{
		ft_printf("Error: Failed to parse the map.\n");
		return (1);
	}
	fdf.mlx_ptr = mlx_init();
	if (!fdf.mlx_ptr)
		return (1);
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");

	init_image(&fdf);	  // Create an image buffer
	init_transform(&fdf); // Set scale and offset
	fdf.z_scale = 0.3f;
	update_window(&fdf);  // Draw + display image
	mlx_key_hook(fdf.win_ptr, handle_key, &fdf);
	mlx_hook(fdf.win_ptr, 17, 0, handle_close, &fdf);
	mlx_loop(fdf.mlx_ptr); // Enter MiniLibX main loop
	return (0);
}
