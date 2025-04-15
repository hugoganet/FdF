/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:11:22 by hganet            #+#    #+#             */
/*   Updated: 2025/04/15 11:45:52 by hganet           ###   ########.fr       */
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
void	init_image(t_fdf *fdf)
{
	fdf->img.img_ptr = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img.img_ptr)
	{
		ft_printf("Error: Failed to create an image.\n");
		exit(1);
	}
	fdf->img.addr = mlx_get_data_addr(
			fdf->img.img_ptr,
			&fdf->img.bits_per_pixel,
			&fdf->img.line_length,
			&fdf->img.endian);
	fdf->img.width = WIN_WIDTH;
	fdf->img.height = WIN_HEIGHT;
}
