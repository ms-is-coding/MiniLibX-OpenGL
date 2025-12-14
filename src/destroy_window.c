/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:46:02 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/14 22:08:44 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlx.h"

int	mlx_destroy_window(t_mlx *mlx, t_window *win)
{
	(void)mlx;
	if (win->texture_id)
		glDeleteTextures(1, &win->texture_id);
	if (win->pbo_ids[0])
	{
		glDeleteBuffers(2, win->pbo_ids);
		win->pbo_ids[0] = 0;
		win->pbo_ids[1] = 0;
	}
	if (win->pixel_buffer)
	{
		free(win->pixel_buffer);
		win->pixel_buffer = NULL;
	}
	if (win->xwin)
		XDestroyWindow(mlx->dpy, win->xwin);
	free(win);
	return (0);
}
