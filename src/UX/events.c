/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugoganet <hugoganet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:42:16 by hganet            #+#    #+#             */
/*   Updated: 2025/04/23 17:24:29 by hugoganet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

/**
 * @brief Called when the ESC key is pressed.
 *
 * Closes the window and exits the program.
 *
 * @param keycode The key that was pressed.
 * @param param Pointer to the FDF structure (passed as void*).
 * @return Always returns 0 (MiniLibX requires it).
 */
int	handle_key(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keycode == 53)
		cleanup_and_exit(fdf, 0, "Program closed with ESC.");
	return (0);
}

/**
 * @brief Called when the window close button (red cross) is clicked.
 *
 * Properly exits the program when the user clicks the window close button.
 *
 * @param param Pointer to the FDF structure (passed as void*).
 * @return Always returns 0.
 */
int	handle_close(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	cleanup_and_exit(fdf, 0, "Program closed with window cross.");
	return (0);
}
