/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:54:27 by hugoganet         #+#    #+#             */
/*   Updated: 2025/04/21 15:20:47 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_fdf	fdf;

	ft_bzero(&fdf, sizeof(t_fdf));
	if (!check_args(ac, av))
		return (1);
	fdf.map = parse_map(av[1], &fdf);
	if (!fdf.map)
		cleanup_and_exit(&fdf, 1, "Error parsing the map");
	if (!init_window(&fdf))
		cleanup_and_exit(&fdf, 1, "Error initializing window");
	init_image(&fdf);
	init_transform(&fdf);
	update_window(&fdf);
	mlx_key_hook(fdf.win_ptr, handle_key, &fdf);
	mlx_hook(fdf.win_ptr, 17, 0, handle_close, &fdf);
	mlx_loop(fdf.mlx_ptr);
	return (0);
}
