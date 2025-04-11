/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:56:21 by hugoganet         #+#    #+#             */
/*   Updated: 2025/04/11 15:41:26 by hganet           ###   ########.fr       */
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
int count_columns(char *line)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i] && line[i] != ' ')
		{
			count++;
			while (line[i] && line[i] != ' ')
				i++;
		}
	}
	return (count);
}

/**
 * @brief Parses a line of altitudes into an array of t_point.
 *
 * This allocates a new array of t_point for the row, and sets each point's
 * x/y/z values. It also updates fdf->min_z and fdf->max_z during parsing.
 *
 * @param fdf Pointer to the FDF context to update min/max z.
 * @param line A single string line from the map.
 * @param y Row index of this line.
 * @param columns Number of expected columns.
 * @return t_point* Array of parsed points for the row.
 */
t_point *parse_line(t_fdf *fdf, char *line, int y, int columns)
{
	t_point *points;
	char **values;
	int i;
	int z;

	points = malloc(sizeof(t_point) * columns);
	if (!points)
		return (NULL);
	values = ft_split(line, ' ');
	if (!values)
	{
		free(points);
		return (NULL);
	}
	i = 0;
	while (values[i] != NULL && i < columns)
	{
		points[i].x = i;
		points[i].y = y;
		points[i].z = ft_atoi(values[i]);
		z = points[i].z;
		if (y == 0 && i == 0)
		{
			fdf->min_z = z;
			fdf->max_z = z;
		}
		else
		{
			if (z < fdf->min_z)
				fdf->min_z = z;
			if (z > fdf->max_z)
				fdf->max_z = z;
		}
		free(values[i]);
		i++;
	}
	free(values);
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
static int get_rows_and_columns(char *filename, int *columns)
{
	int fd;
	char *line;
	int rows;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	rows = 0;
	while ((line = get_next_line(fd)))
	{
		if (rows == 0)
			*columns = count_columns(line);
		free(line);
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
static t_point **read_map_file(int fd, t_fdf *fdf, int rows, int columns)
{
	t_point **map;
	char *line;
	int i;

	map = malloc(sizeof(t_point *) * rows);
	if (!map)
		return (NULL);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		map[i] = parse_line(fdf, line, i, columns);
		free(line);
		if (!map[i])
			return (NULL);
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
t_point **parse_map(char *filename, t_fdf *fdf)
{
	t_point **map;
	int fd;

	fdf->rows = get_rows_and_columns(filename, &fdf->columns);
	if (fdf->rows <= 0)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = read_map_file(fd, fdf, fdf->rows, fdf->columns);
	close(fd);
	return (map);
}