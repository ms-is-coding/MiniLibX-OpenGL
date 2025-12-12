/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image_to_window.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:33:28 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/12 17:52:55 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "mlx.h"

int	mlx_put_image_to_window(t_mlx *mlx, void *win_ptr, void *img_ptr, int x,
		int y)
{
	t_window	*win;
	t_img		*img;
	int			copy_w;
	int			copy_h;
	int			i;
	int			offset_win;
	int			offset_img;
	int			src_x;
	int			src_y;

	(void)mlx;
	win = (t_window *)win_ptr;
	img = (t_img *)img_ptr;
	if (!win || !win->pixel_buffer || !img || !img->buffer)
		return (0);
	if (x >= win->width || y >= win->height || x + img->width <= 0
		|| y + img->height <= 0)
		return (0);
	src_x = 0;
	src_y = 0;
	copy_w = img->width;
	copy_h = img->height;
	if (x < 0)
	{
		src_x = -x;
		copy_w += x;
		x = 0;
	}
	if (y < 0)
	{
		src_y = -y;
		copy_h += y;
		y = 0;
	}
	if (x + copy_w > win->width)
		copy_w = win->width - x;
	if (y + copy_h > win->height)
		copy_h = win->height - y;
	i = 0;
	while (i < copy_h)
	{
		offset_img = (src_y + i) * img->width + src_x;
		offset_win = (y + i) * win->width + x;
		memcpy(win->pixel_buffer + offset_win,
			img->buffer + offset_img,
			copy_w * sizeof(int));
		i++;
	}
	return (0);
}
