/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_put.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 14:07:30 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/20 15:25:49 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "mlx.h"

typedef struct s_text_info {
	int	w;
	int	h;
	int	ascent;
	int	padding;
}	t_text_info;

typedef struct s_blend_info {
	int	x_off;
	int	y_off;
	int	color;
	int	padding;
}	t_blend_info;

static void	blend_text_to_buffer(t_window *win, XImage *img,
		const t_blend_info bi)
{
	int	x;
	int	y;
	int	win_idx;

	y = -1;
	while (++y < img->height)
	{
		if (y + bi.y_off < 0 || y + bi.y_off >= win->height)
			continue ;
		x = -1;
		while (++x < img->width)
		{
			if (x + bi.x_off < 0 || x + bi.x_off >= win->width)
				continue ;
			if (XGetPixel(img, x, y) & 0x00FFFFFF)
			{
				win_idx = (y + bi.y_off) * win->width + (x + bi.x_off);
				win->pixel_buffer[win_idx] = bi.color;
			}
		}
	}
}

static XImage	*rasterize_text(t_mlx *mlx, t_window *win, const char *str,
		const t_text_info *t)
{
	Pixmap	pmap;
	XImage	*img;

	pmap = XCreatePixmap(mlx->dpy, win->xwin, t->w, t->h, mlx->vi->depth);
	if (!pmap)
		return (NULL);
	XSetForeground(mlx->dpy, mlx->gc, 0xFFFFFFFF);
	XSetBackground(mlx->dpy, mlx->gc, 0x00000000);
	XFillRectangle(mlx->dpy, pmap, mlx->gc, 0, 0, t->w, t->h);
	XDrawString(mlx->dpy, pmap, mlx->gc, 0, t->ascent, str, strlen(str));
	img = XGetImage(mlx->dpy, pmap, 0, 0, t->w, t->h, AllPlanes, ZPixmap);
	XFreePixmap(mlx->dpy, pmap);
	return (img);
}

static void	get_text_layout(t_mlx *mlx, const char *str, t_text_info *info)
{
	int			dir;
	int			descent;
	XCharStruct	overall;

	XTextExtents(mlx->font, str, strlen(str), &dir, &info->ascent,
		&descent, &overall);
	info->w = overall.width;
	info->h = info->ascent + descent;
}

int	mlx_string_put(t_mlx *mlx, t_window *win, const int x, const int y,
		const int color, const char *string)
{
	t_text_info	info;
	XImage		*img;

	if (!mlx || !win || !string || !mlx->font)
		return (0);
	get_text_layout(mlx, string, &info);
	if (x + info.w < 0 || x >= win->width || y + info.h < 0 || y >= win->height)
		return (0);
	img = rasterize_text(mlx, win, string, &info);
	if (img)
	{
		blend_text_to_buffer(win, img,
			(t_blend_info){x, y - info.ascent, color, 0});
		XDestroyImage(img);
	}
	return (0);
}
