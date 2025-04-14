/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:47:40 by hganet            #+#    #+#             */
/*   Updated: 2025/04/14 13:47:20 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Interpolates between two colors based on a percentage.
 *
 * @param start Starting color (hex).
 * @param end Ending color (hex).
 * @param percent A float from 0.0 to 1.0.
 * @return int Resulting color in hex.
 */
int	interpolate_color(int start, int end, float percent)
{
	int	r;
	int	g;
	int	b;

	r = ((int)((1 - percent) * ((start >> 16) & 0xFF) + percent * ((end >> 16) & 0xFF))) << 16;
	g = ((int)((1 - percent) * ((start >> 8) & 0xFF) + percent * ((end >> 8) & 0xFF))) << 8;
	b = (int)((1 - percent) * (start & 0xFF) + percent * (end & 0xFF));
	return (r | g | b);
}

/**
 * @brief Returns a smoothly interpolated color from a gradient.
 *
 * @param z Height of the current point.
 * @param min_z Lowest height in the map.
 * @param max_z Highest height in the map.
 * @return int The resulting hex color.
 */
int	get_color(int z, int min_z, int max_z)
{
	float	percent;

	if (max_z == min_z)
		return (0xFFFFFF); // Flat map
	percent = (float)(z - min_z) / (max_z - min_z);
	return (interpolate_color(0x0000FF, 0xFF0000, percent)); // Blue → Red
}
