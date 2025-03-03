/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugoganet <hugoganet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:56:21 by hugoganet         #+#    #+#             */
/*   Updated: 2025/03/03 17:18:37 by hugoganet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"

/**
 * @brief Counts the number of columns (numbers) in a row.
 *
 * @param line The input line from the map.
 * @return int The count of numbers found.
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
 * @brief Parses a single line into an array of points.
 *
 * @param line The line containing altitude values.
 * @param y The current row index.
 * @param columns The number of columns expected.
 * @return t_point* The array of points for the row.
 */
t_point *parse_line(char *line, int y, int columns)
{
	t_point *points; // Initialize the array of points for the row
	char 	**values; // Initialize the array of values (strings)
	int 	i;

	points = malloc(sizeof(t_point) * columns); // Allocate memory for the array of points
	if (!points)
		return (NULL);
	values = ft_split(line, ' '); // Split the line into an array of strings (values)
	if (!values) // Check if the values were split correctly (no memory error)		
	{
		free(points);
		return (NULL);
	}
	i = 0;
	while (i < columns) // Iterate over the values and store them in the array of points
	{
		// ? Can I not use the -> operator to access the struct members ?
		points[i].x = i; // Set the x-coordinate to the index(column) as the map is 2D
		points[i].y = y; // Set the y-coordinate to the row index
		points[i].z = ft_atoi(values[i]); // Set the z-coordinate to the altitude value
		// ! Each row as 19 points, each point has 3 values (x, y and z)
		//printf("%i %i %i\n", points[i].x, points[i].y, points[i].z);
		free(values[i]); // Free the value of the column after storing it
		i++;
	}
	free(values); // Free the array of values after storing all the points
	return (points); // Return the array of points
}

/**
 * @brief Gets the number of rows and sets the column count from the file by reading it line by line.
 *
 * @param filename The name of the map file.
 * @param columns Pointer to store the number of columns.
 * @return int The number of rows, or -1 on error.
 */
static int get_rows_and_columns(char *filename, int *columns)
{
	int fd;
	char *line;
	int rows;

	rows = 0;
	fd = open(filename, O_RDONLY); // Open the file with its filename
	if (fd < 0)
		return (-1);
	while ((line = get_next_line(fd))) // Read the file line by line
	{
		if (rows == 0) // Get the number of columns from the first line
		{
			*columns = count_columns(line); // ? Do I need to check if the number of columns is the same for each row ?
		}
		//ft_printf("%s\n", line);
		rows++; // Increment the number of rows each time a line is read
		free(line); //Free the line before reading the next one
	}
	close(fd);
	return (rows);
}

/**
 * @brief Reads the map file and fills the 2D array of points.
 *
 * @param fd The file descriptor.
 * @param rows The number of rows.
 * @param columns The number of columns.
 * @return t_point** The 2D array representing the map.
 */
static t_point **read_map_file(int fd, int rows, int columns)
{
	t_point **map; // Initialize the 2D array of points
	int 	i; // Incremental var for the rows
	char 	*line; // Initialize the line buffer

	// ? Why do I not multiply by the number of columns ? It should be size of(t_point *) * rows * columns ?
	// I malloc a pointer of t_point for each row, so it is actually an array of array(t_point). I will allocate for each row the number of columns in parse_line.
	map = malloc(sizeof(t_point *) * rows); // Allocate memory for the 2D array
	if (!map)
		return (NULL);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		map[i] = parse_line(line, i, columns); // Parse the line into an array of points
		free(line); // Free the line buffer after parsing it
		if (!map[i])
			return (NULL);
		i++;
	}
	return (map);
}

/**
 * @brief Parses the entire map file.
 *
 * @param filename The name of the map file.
 * @param rows Pointer to store the number of rows.
 * @param columns Pointer to store the number of columns.
 * @return t_point** The 2D array representing the map.
 */
t_point **parse_map(char *filename, int *rows, int *columns)
{
	t_point **map; // 2D array of points 
	int fd; // File descriptor

	*rows = get_rows_and_columns(filename, columns);
	if (*rows <= 0) // Check if the number of rows is valid
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = read_map_file(fd, *rows, *columns);
	close(fd);
	return (map);
}
