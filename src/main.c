/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:54:27 by hugoganet         #+#    #+#             */
/*   Updated: 2025/04/15 11:30:34 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_fdf	fdf;

	if (ac != 2)
	{
		ft_printf("Usage: %s <map.fdf>\n", av[0]);
		return (1);
	}
	fdf.map = parse_map(av[1], &fdf);
	if (!fdf.map)
	{
		ft_printf("Error: Failed to parse the map.\n");
		return (1);
	}
	if (!init_window(&fdf))
		cleanup_and_exit(&fdf, 1);
	init_image(&fdf);
	init_transform(&fdf);
	update_window(&fdf);
	mlx_key_hook(fdf.win_ptr, handle_key, &fdf);
	mlx_hook(fdf.win_ptr, 17, 0, handle_close, &fdf);
	mlx_loop(fdf.mlx_ptr);
	cleanup_and_exit(&fdf, 0);
	return (0);
}
