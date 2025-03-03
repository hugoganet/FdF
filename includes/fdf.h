#ifndef FDF_H
#define FDF_H

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "mlx.h" // Include MiniLibX

/**
 * @brief Structure representing a point in 3D space.
 * X, Y, and Z coordinates are stored as integers.
 * The Z-coordinate represents the altitude.
 * The X and Y coordinates are used for rendering.
 * [x, y, z] -> [x, y] (2D)
 * (0, 0, 0) -> (0, 0)
 * (1, 0, 0) -> (1, 0)
 * (0, 1, 0) -> (0, 1)
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
	void *mlx_ptr; // MiniLibX instance
	void *win_ptr; // Window instance
	t_img img;	   // Image buffer for rendering
	t_point **map; // 2D array of points
	int rows;
	int columns;
} t_fdf;

// Parsing functions
t_point **parse_map(char *filename, int *rows, int *columns);
t_point *parse_line(char *line, int y, int columns);
int count_columns(char *line);

// Rendering functions
void put_pixel_to_image(t_img *img, int x, int y, int color);
void draw_line(t_fdf *fdf, t_point p1, t_point p2, int color);
void draw_map(t_fdf *fdf);
void render_image(t_fdf *fdf);

#endif
