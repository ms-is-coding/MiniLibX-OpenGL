/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image_to_window.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:33:28 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/13 20:58:38 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "mlx.h"

typedef struct s_draw_ctx
{
	int	x;
	int	y;
	int	copy_w;
	int	copy_h;
	int	src_x;
	int	src_y;
}	t_draw_ctx;

static void	calc_clipping(t_window *win, t_draw_ctx *ctx)
{
	if (ctx->x < 0)
	{
		ctx->src_x = -ctx->x;
		ctx->copy_w += ctx->x;
		ctx->x = 0;
	}
	if (ctx->y < 0)
	{
		ctx->src_y = -ctx->y;
		ctx->copy_h += ctx->y;
		ctx->y = 0;
	}
	if (ctx->x + ctx->copy_w > win->width)
		ctx->copy_w = win->width - ctx->x;
	if (ctx->y + ctx->copy_h > win->height)
		ctx->copy_h = win->height - ctx->y;
}

static void	draw_lines(t_window *win, t_img *img, t_draw_ctx *ctx)
{
	int	i;
	int	offset_win;
	int	offset_img;

	i = 0;
	while (i < ctx->copy_h)
	{
		offset_img = (ctx->src_y + i) * img->width + ctx->src_x;
		offset_win = (ctx->y + i) * win->width + ctx->x;
		memcpy(win->pixel_buffer + offset_win,
			img->buffer + offset_img,
			ctx->copy_w * sizeof(int));
		i++;
	}
}

int	mlx_put_image_to_window(t_mlx *mlx, void *win_ptr, void *img_ptr, int x,
		int y)
{
	t_window	*win;
	t_img		*img;
	t_draw_ctx	ctx;

	(void)mlx;
	win = (t_window *)win_ptr;
	img = (t_img *)img_ptr;
	if (!win || !win->pixel_buffer || !img || !img->buffer)
		return (0);
	if (x >= win->width || y >= win->height || x + img->width <= 0
		|| y + img->height <= 0)
		return (0);
	ctx.src_x = 0;
	ctx.src_y = 0;
	ctx.copy_w = img->width;
	ctx.copy_h = img->height;
	ctx.x = x;
	ctx.y = y;
	calc_clipping(win, &ctx);
	draw_lines(win, img, &ctx);
	return (0);
}
