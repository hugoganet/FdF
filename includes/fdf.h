/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:53:01 by hganet            #+#    #+#             */
/*   Updated: 2025/04/14 15:37:50 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "mlx.h"
#include <math.h>

/**
 * @brief Structure representing a point in 3D space.
 * X, Y, and Z coordinates are stored as integers.
 */
typedef struct s_point
{
	int x; // X-coordinate
	int y; // Y-coordinate
	int z; // Z-coordinate
} t_point;

/**
 * @brief Structure representing an image buffer in MiniLibX.
 */
typedef struct s_img
{
	void *img_ptr;		// Pointer to the MiniLibX image
	char *addr;			// Address of the image memory
	int bits_per_pixel; // Bits per pixel (color depth)
	int line_length;	// Length of a line in bytes
	int endian;			// Endian format of the image
	int width;			// Width of the image
	int height;			// Height of the image
} t_img;

/**
 * @brief Structure representing the FDF application.
 */
typedef struct s_fdf
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_point	**map; // 2D array of points representing the map. Each pointer is a row of points
	int		rows;
	int		columns;
	int		min_z;
	int		max_z;
	float	z_scale;

	float	scale;  // Dynamic zoom factor
	int		x_offset; // Center offset on X
	int		y_offset; // Center offset on Y
} t_fdf;

/**
 * @brief Structure representing a line in 2D space.
 * This is used for drawing lines between points.
 */
typedef struct s_line
{
	t_point p1;	 // Starting point
	t_point p2;	 // Ending point
	int delta_x; // Difference in x
	int delta_y; // Difference in y
	int step_x;	 // Direction for x (+1 or -1)
	int step_y;	 // Direction for y (+1 or -1)
	int err;	 // Current error value
	int color;	 // Color of the line
} t_line;


// ───────────────────────────────────────────────
// PARSING FUNCTIONS

int count_columns(char *line);
int fill_points_array(t_fdf *fdf, t_point *points, char **values, int y, int columns);
t_point *parse_line(t_fdf *fdf, char *line, int y, int columns);
t_point **parse_map(char *filename, t_fdf *fdf);
void free_map_rows(t_point **map, int up_to);
void free_split_array(char **array);
void update_minmax_z(t_fdf *fdf, int z);

// ───────────────────────────────────────────────
// DRAWING & RENDERING FUNCTIONS

void draw_vertical_line(t_fdf *fdf, int x, int y);
void draw_horizontal_line(t_fdf *fdf, int x, int y);
void draw_line(t_fdf *fdf, t_point p1, t_point p2, int color);
void draw_map(t_fdf *fdf);
int get_color(int z, int min_z, int max_z);
void init_image(t_fdf *fdf);
void init_transform(t_fdf *fdf);
void put_pixel_to_image(t_img *img, int x, int y, int color);
t_point project_point(t_point p, t_fdf *fdf);
void render_image(t_fdf *fdf);
void update_window(t_fdf *fdf);

// ───────────────────────────────────────────────
// EVENT & UX HANDLING FUNCTIONS

void cleanup_and_exit(t_fdf *fdf, int exit_code);
int handle_close(void *param);
int handle_key(int keycode, void *param);

#define WIN_WIDTH 1600
#define WIN_HEIGHT 1200

#endif
