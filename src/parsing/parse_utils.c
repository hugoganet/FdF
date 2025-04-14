/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:33:49 by hganet            #+#    #+#             */
/*   Updated: 2025/04/14 12:50:54 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Updates fdf->min_z and fdf->max_z based on a given z.
 */
void update_minmax_z(t_fdf *fdf, int z)
{
	if (z < fdf->min_z)
		fdf->min_z = z;
	if (z > fdf->max_z)
		fdf->max_z = z;
}

/**
 * @brief Fills an array of t_point from the split values and updates min/max z.
 * 
 * @param fdf The FDF context.
 * @param points The array of t_point to fill.
 * @param values The split values from the line.
 * @param y The current row index.
 * @param columns The number of columns in the map.
 * @return 1 on success, 0 on failure.
 */
int fill_points_array(t_fdf *fdf, t_point *points, char **values, int y, int columns)
{
	int i;
	int z;

	i = 0;
	// Loop through the split values and numbers of columns
	while (i < columns && values[i])
	{
		// x is the column index
		points[i].x = i;
		// y is the row index
		points[i].y = y;
		// z is the actual value 
		points[i].z = ft_atoi(values[i]);
		// Update the z value
		z = points[i].z;
		// If this is first row and first column
		if (y == 0 && i == 0)
		{
			// Initialize the structure's min_z and max_z to the first z value
			fdf->min_z = z;
			fdf->max_z = z;
		}
		else
			// Update the min and max z values based on the current z
			update_minmax_z(fdf, z);
		i++;
	}
	return (1);
}


