/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:33:49 by hganet            #+#    #+#             */
/*   Updated: 2025/04/18 17:52:06 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * * @brief Checks the command line arguments for validity.
 */
int	check_args(int ac, char **av)
{
	int		len;
	char	*ext;

	if (ac != 2)
	{
		ft_printf("Usage: %s <map.fdf>\n", av[0]);
		return (0);
	}
	len = ft_strlen(av[1]);
	if (len < 5)
	{
		ft_printf("Error: Filename too short or missing .fdf extension.\n");
		return (0);
	}
	ext = av[1] + len - 4;
	if (ft_strncmp(ext, ".fdf", 4) != 0)
	{
		ft_printf("Error: File must end with .fdf extension.\n");
		return (0);
	}
	return (1);
}

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
 * @brief Fills a single t_point from a split value like "42,0xFF0000".
 * 
 * This function extracts the x, y, z, and color values from the input string
 * and assigns them to the corresponding fields in the t_point structure.
 * @param in Pointer to the t_point_input structure containing the input data.
 * @param i Index of the current point in the input array.
 */
static void	fill_point(t_point_input *in, int i)
{
	char	**parts;
	int		z;

	parts = ft_split(in->values[i], ',');
	in->points[i].x = i;
	in->points[i].y = in->y;
	in->points[i].z = ft_atoi(parts[0]);
	in->points[i].color = -1;
	if (parts[1])
		in->points[i].color = ft_atoi_base(parts[1], 16);
	free_split_array(parts);
	z = in->points[i].z;
	if (in->y == 0 && i == 0)
	{
		in->fdf->min_z = z;
		in->fdf->max_z = z;
	}
	else
		update_minmax_z(in->fdf, z);
}

/**
 * @brief Fills the points array with t_point structures.
 * @param input The t_point_input structure containing the input data.
 * @return 1 on success, 0 on failure.
 */
int	fill_points_array(t_point_input input)
{
	int	i;

	i = 0;
	while (i < input.columns && input.values[i])
	{
		fill_point(&input, i);
		i++;
	}
	return (1);
}
