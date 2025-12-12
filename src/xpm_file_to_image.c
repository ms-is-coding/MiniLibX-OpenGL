/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_file_to_image.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:47:59 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/12 17:53:35 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/xpm.h>

#include "mlx.h"

static void	fill_image_buffer(const t_img *img, XImage *x_img, XImage *x_mask)
{
	int				x;
	int				y;
	unsigned int	pixel;
	bool			is_transparent;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			pixel = XGetPixel(x_img, x, y);
			is_transparent = false;
			if (x_mask)
			{
				if (XGetPixel(x_mask, x, y) == 0)
					is_transparent = true;
			}
			if (is_transparent)
				img->buffer[y * img->width + x] = 0x00000000;
			else
				img->buffer[y * img->width + x] = (int)(pixel | 0xFF000000);
			x++;
		}
		y++;
	}
}

void	*mlx_xpm_file_to_image(t_mlx *mlx, char *filename,
			int *width, int *height)
{
	t_img			*img;
	XImage			*x_img;
	XImage			*x_mask;
	XpmAttributes	attr;
	int				ret;

	if (!mlx || !filename)
		return (NULL);
	attr.valuemask = XpmReturnPixels | XpmReturnExtensions | XpmSize;
	x_img = NULL;
	x_mask = NULL;
	ret = XpmReadFileToImage(mlx->dpy, filename, &x_img, &x_mask, &attr);
	if (ret != XpmSuccess || !x_img)
	{
		if (x_img)
			XDestroyImage(x_img);
		if (x_mask)
			XDestroyImage(x_mask);
		return (NULL);
	}
	img = mlx_new_image(mlx, x_img->width, x_img->height);
	if (img)
	{
		fill_image_buffer(img, x_img, x_mask);
		if (width)
			*width = x_img->width;
		if (height)
			*height = x_img->height;
	}
	XDestroyImage(x_img);
	if (x_mask)
		XDestroyImage(x_mask);
	XpmFreeAttributes(&attr);
	return (img);
}
