/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:24:54 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/13 20:12:05 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlx.h"

int	mlx_destroy_image(t_mlx *mlx, void *img_ptr)
{
	t_img	*img;

	(void)mlx;
	img = (t_img *)img_ptr;
	if (img)
	{
		if (img->buffer)
			free(img->buffer);
		free(img);
	}
	return (0);
}
