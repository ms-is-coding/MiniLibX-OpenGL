/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_addr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:33:17 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/12 17:04:16 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

char	*mlx_get_data_addr(void *img_ptr, int *bpp, int *line_len, int *endian)
{
	t_img	*img;

	img = (t_img *)img_ptr;
	if (!img)
		return (NULL);
	if (bpp)
		*bpp = img->bpp;
	if (line_len)
		*line_len = img->line_len;
	if (endian)
		*endian = img->endian;
	return ((char *)img->buffer);
}
