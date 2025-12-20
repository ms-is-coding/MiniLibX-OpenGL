/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_font.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 14:07:34 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/20 15:08:29 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "mlx.h"

int	mlx_set_font(t_mlx *mlx, t_window *win, const char *name)
{
	XFontStruct	*font;

	(void)win;
	if (!mlx || !name)
		return (1);
	font = XLoadQueryFont(mlx->dpy, name);
	if (!font)
	{
		fprintf(stderr, "Warning: Could not load font '%s'\n", name);
		return (1);
	}
	if (mlx->font)
		XFreeFont(mlx->dpy, mlx->font);
	mlx->font = font;
	XSetFont(mlx->dpy, mlx->gc, font->fid);
	return (0);
}
