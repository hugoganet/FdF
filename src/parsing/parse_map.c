/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:56:21 by hugoganet         #+#    #+#             */
/*   Updated: 2025/04/14 12:02:26 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"

/**
 * @brief Counts how many numbers (columns) are in a single line of the map.
 *
 * A column is counted when we go from a space into a non-space character.
 *
 * @param line A single row of the map, as a string.
 * @return int The number of numeric values (columns) found in the line.
 */
int	count_columns(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	// Loop through the line until we reach the end
	while (line[i])
	{
		// Skip spaces
		while (line[i] == ' ')
			i++;
		// If we find a non-space character, increment the column count
		if (line[i] && line[i] != ' ')
		{
			count++;
			//Move to the next space
			while (line[i] && line[i] != ' ')
				i++;
		}
	}
	return (count);
}

/**
 * @brief Parses a line of the .fdf file into an array of t_point.
 *
 * @param fdf Pointer to the FDF context.
 * @param line A single line of text from the map file.
 * @param y The current row index.
 * @param columns The expected number of columns.
 * @return t_point* A dynamically allocated array of t_point or NULL on error.
 */
t_point	*parse_line(t_fdf *fdf, char *line, int y, int columns)
{
	t_point	*points;
	char	**values;

	// Allocate memory for the t_points array (row)
	points = malloc(sizeof(t_point) * columns);
	if (!points)
		return (NULL);
	// Split the line into values
	values = ft_split(line, ' ');
	if (!values)
		return (free(points), NULL);
	// Fill the points array with parsed values
	if (!fill_points_array(fdf, points, values, y, columns))
	// If fill_points_array fails, free the points array
		return (free(points), NULL);
	// Free the split array of strings
	free_split_array(values);
	return (points);
}

/**
 * @brief Opens the file and counts how many rows and columns it has.
 *
 * It only counts the first line's columns and assumes all others are the same.
 *
 * @param filename The file path to open.
 * @param columns Pointer to write the column count into.
 * @return int Number of rows in the map, or -1 on error.
 */
static int	get_rows_and_columns(char *filename, int *columns)
{
	int		fd;
	char	*line;
	int		rows;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	rows = 0;
	// Loop until EOF (breaks when get_next_line returns NULL)
	while (1)
	{
		// Read a line from the file
		line = get_next_line(fd);
		// If the line is NULL, we reached EOF or an error occurred
		if (!line)
			break ;
		// If it's the first line, count the columns
		if (rows == 0)
			*columns = count_columns(line);
		// Free the line after processing
		free(line);
		// Increment the row count
		rows++;
	}
	close(fd);
	return (rows);
}

/**
 * @brief Reads each line of the map file and fills the map 2D array.
 *
 * Calls parse_line() for each line and builds a full array of t_point* lines.
 *
 * @param fd Open file descriptor for the map file.
 * @param fdf Pointer to the FDF structure.
 * @param rows Total number of rows.
 * @param columns Total number of columns.
 * @return t_point** 2D array of points, or NULL on error.
 */
static t_point	**read_map_file(int fd, t_fdf *fdf, int rows, int columns)
{
	/** t_point = {
	*		x: 0,
	*		y: 0,
	*		z: 0
	*	};
	*	t_point * = array of t_point (a row)
	*	t_point ** = pointer to an aray of t_point
	*/
	t_point	**map;
	char	*line;
	int		i;

	// Allocate memory for the map array
	map = malloc(sizeof(t_point *) * rows);
	if (!map)
		return (NULL);
	i = 0;
	// Loop through each line of the file
	while (i < rows)
	{
		// Read a line from the file
		line = get_next_line(fd);
		if (!line)
			break ;
		// Parse the line into a t_point array. map[i] is a row of points
		map[i] = parse_line(fdf, line, i, columns);
		// Free the allocated memory in ft_split 
		free(line);
		// If parsing fails, free the map previously allocated rows
		if (!map[i])
		{
			free_map_rows(map, i);
			return (NULL);
		}
		i++;
	}
	return (map);
}

/**
 * @brief Parses a complete map file and builds the 2D point grid.
 *
 * This sets fdf->rows, fdf->columns, fdf->min_z and fdf->max_z.
 *
 * @param filename The map file path (e.g., "42.fdf").
 * @param fdf Pointer to the FDF structure.
 * @return t_point** The 2D array of points for the map.
 */
t_point	**parse_map(char *filename, t_fdf *fdf)
{
	t_point	**map;
	int		fd;

	// Return the row count directly in fdf->rows, and set fdf->columns by reference
	fdf->rows = get_rows_and_columns(filename, &fdf->columns);
	// If rows are less than or equal to 0, return NULL
	if (fdf->rows <= 0)
		return (NULL);
	// Open the file for reading
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	// Read the map file and fill the 2D array of points
	map = read_map_file(fd, fdf, fdf->rows, fdf->columns);
	// Close the file descriptor
	close(fd);
	return (map);
}
