/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:46:02 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/21 12:52:22 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlx.h"

int	mlx_destroy_window(t_mlx *mlx, t_window *win)
{
	if (!mlx || !win)
		return (0);
	if (win->texture_id)
		glDeleteTextures(1, &win->texture_id);
	if (win->pbo_ids[0])
	{
		glDeleteBuffers(2, win->pbo_ids);
		win->pbo_ids[0] = 0;
	}
	if (win->pixel_buffer)
	{
		free(win->pixel_buffer);
		win->pixel_buffer = NULL;
	}
	if (win->gc)
	{
		XFreeGC(mlx->dpy, win->gc);
		win->gc = NULL;
	}
	if (win->glc)
	{
		glXDestroyContext(mlx->dpy, win->glc);
		win->glc = NULL;
	}
	if (win->cmap)
	{
		XFreeColormap(mlx->dpy, win->cmap);
		win->cmap = 0;
	}
	if (win->xwin)
		XDestroyWindow(mlx->dpy, win->xwin);
	free(win);
	return (0);
}
