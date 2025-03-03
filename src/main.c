/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugoganet <hugoganet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:54:27 by hugoganet         #+#    #+#             */
/*   Updated: 2025/03/03 14:00:54 by hugoganet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

	if (argc != 2)
	{
		ft_printf("Usage: %s <map.fdf>\n", argv[0]);
		return (1);
	}
	// Parse the map file
	fdf.map = parse_map(argv[1], &fdf.rows, &fdf.columns); // Store the returned 2D array in the fdf structure
	if (!fdf.map)
	{
		ft_printf("Error: Failed to parse the map.\n");
		return (1);
	}
	/*
	// Initialize the MiniLibX context
	fdf.mlx_ptr = mlx_init();
	if (!fdf.mlx_ptr)
		return (1);
	// Create a new window
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, 800, 600, "FDF");
	// Draw the map
	draw_map(&fdf);
	// Render the image
	mlx_loop(fdf.mlx_ptr);
	*/
	return (0);
}
