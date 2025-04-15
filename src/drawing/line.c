/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:07:53 by hganet            #+#    #+#             */
/*   Updated: 2025/04/15 11:43:23 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Initializes a t_line structure to prepare for Bresenham's line drawing.
 *
 * Sets all parameters required for stepping from p1 to p2 using integer math.
 * This includes delta (distance), step (direction), error (decision value),
 * and color (used for all pixels along the line).
 *
 * @param line Pointer to the t_line structure to initialize.
 * @param p1 Starting point of the line (in screen coordinates).
 * @param p2 Ending point of the line (in screen coordinates).
 * @param color Color to apply to every pixel on the line in hex.
 */
static void	init_line(t_line *line, t_point p1, t_point p2, int color)
{
	line->p1 = p1;
	line->p2 = p2;
	line->color = color;
	line->delta_x = abs(p2.x - p1.x);
	line->delta_y = abs(p2.y - p1.y);
	if (p1.x < p2.x)
		line->step_x = 1;
	else
		line->step_x = -1;
	if (p1.y < p2.y)
		line->step_y = 1;
	else
		line->step_y = -1;
	line->err = line->delta_x - line->delta_y;
}

/**
 * @brief Draws a line from p1 to p2 using Bresenham's algorithm.
 *
 * This function walks pixel by pixel from p1 to p2, deciding at each step
 * whether to move horizontally, vertically, or diagonally,
 * in order to approximate a straight line.
 * It uses only integer arithmetic for efficiency.
 *
 * @param fdf Pointer to the FDF structure (for accessing the image).
 * @param line Pointer to the t_line structure,
 * 	 	  already initialized with delta, step, err, etc.
 */
static void	draw_line_loop(t_fdf *fdf, t_line *line)
{
	int	e2;

	while (line->p1.x != line->p2.x || line->p1.y != line->p2.y)
	{
		put_pixel_to_image(&fdf->img, line->p1.x, line->p1.y, line->color);
		e2 = line->err * 2;
		if (e2 > -line->delta_y)
		{
			line->err -= line->delta_y;
			line->p1.x += line->step_x;
		}
		if (e2 < line->delta_x)
		{
			line->err += line->delta_x;
			line->p1.y += line->step_y;
		}
	}
}

/**
 * @brief Draws a line between two points using Bresenham's algorithm.
 *
 * Calculates the points on a line by incrementing step-by-step
 * using only integers for performance.
 *
 * @param fdf Pointer to the FDF structure.
 * @param p1 Starting screen-space point.
 * @param p2 Ending screen-space point.
 * @param color Line color.
 */
void	draw_line(t_fdf *fdf, t_point p1, t_point p2, int color)
{
	t_line	line;

	init_line(&line, p1, p2, color);
	draw_line_loop(fdf, &line);
}
