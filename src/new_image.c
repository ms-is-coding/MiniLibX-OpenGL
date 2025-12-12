/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:32:59 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/12 17:01:48 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

void	*mlx_new_image(t_mlx *mlx, const int width, const int height)
{
	t_img	*img;

	(void)mlx;
	if (width <= 0 || height <= 0)
		return (NULL);
	img = calloc(1, sizeof(t_img));
	if (!img)
		return (NULL);
	img->buffer = calloc(width * height, sizeof(int));
	if (!img->buffer)
	{
		free(img);
		return (NULL);
	}
	img->width = width;
	img->height = height;
	img->bpp = 32;
	img->line_len = width * 4;
	img->endian = 0;
	return (img);
}
