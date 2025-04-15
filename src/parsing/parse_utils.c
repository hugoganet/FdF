/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:33:49 by hganet            #+#    #+#             */
/*   Updated: 2025/04/15 11:35:20 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Initializes the window for the FDF application.
 */
int	init_window(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	if (!fdf->mlx_ptr)
		return (0);
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (!fdf->win_ptr)
		return (0);
	return (1);
}

/**
 * @brief Updates fdf->min_z and fdf->max_z based on a given z.
 */
void	update_minmax_z(t_fdf *fdf, int z)
{
	if (z < fdf->min_z)
		fdf->min_z = z;
	if (z > fdf->max_z)
		fdf->max_z = z;
}

/**
 * @brief Fills an array of t_point from the split values and updates min/max z.
 * 
 * @param input The input structure containing the :
 * 			  	fdf, points, values, y, and columns.
 * @return 1 on success, 0 on failure.
 */
int	fill_points_array(t_point_input input)
{
	int	i;
	int	z;

	i = 0;
	while (i < input.columns && input.values[i])
	{
		input.points[i].x = i;
		input.points[i].y = input.y;
		input.points[i].z = ft_atoi(input.values[i]);
		z = input.points[i].z;
		if (input.y == 0 && i == 0)
		{
			input.fdf->min_z = z;
			input.fdf->max_z = z;
		}
		else
			update_minmax_z(input.fdf, z);
		i++;
	}
	return (1);
}
