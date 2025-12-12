/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 03:02:28 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/12 14:32:42 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

int	mlx_pixel_put(t_mlx *mlx, t_window *win, const int x, const int y,
		const int color)
{
	(void)mlx;
	if (!win || !win->pixel_buffer)
		return (0);
	if (x < 0 || x >= win->width || y < 0 || y >= win->height)
		return (0);
	win->pixel_buffer[(y * win->width) + x] = color;
	return (0);
}
