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
	void *mlx_ptr;
	void *win_ptr;
	t_img img;
	t_point **map;
	int rows;
	int columns;
	int min_z;
	int max_z;
	float z_scale;

	float scale;  // Dynamic zoom factor
	int x_offset; // Center offset on X
	int y_offset; // Center offset on Y
} t_fdf;

// Parsing functions
t_point **parse_map(char *filename, t_fdf *fdf);
t_point *parse_line(t_fdf *fdf, char *line, int y, int columns);
int count_columns(char *line);

// Rendering functions
void put_pixel_to_image(t_img *img, int x, int y, int color);
void draw_line(t_fdf *fdf, t_point p1, t_point p2, int color);
void draw_map(t_fdf *fdf);
void render_image(t_fdf *fdf);
void update_window(t_fdf *fdf);
void init_transform(t_fdf *fdf);
void init_image(t_fdf *fdf);
t_point project_point(t_point p, t_fdf *fdf);
int get_color(int z, int min_z, int max_z);
int interpolate_color(int start, int end, float percent);

	// Event functions
	int handle_key(int keycode, void *param);
int handle_close(void *param);


#define WIN_WIDTH 1600
#define WIN_HEIGHT 1200

#endif
