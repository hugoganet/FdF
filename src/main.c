/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugoganet <hugoganet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:54:27 by hugoganet         #+#    #+#             */
/*   Updated: 2025/02/27 19:04:45 by hugoganet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	void *mlx;
	void *win;

	(void)argc;
	(void)argv;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 600, "FdF");
	// Use the win variable, for example, to check if the window was created successfully
	if (!win)
	{
		fprintf(stderr, "Failed to create window\n");
		return 1;
	}
	mlx_loop(mlx);
	return (0);
}
