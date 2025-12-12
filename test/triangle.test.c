/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 01:18:41 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/12 15:24:33 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

int	on_destroy(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	mlx_loop_end(mlx);
	return (0);
}

int	on_keypress(int keysim, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (keysim == XK_Escape)
		mlx_loop_end(mlx);
	return (0);
}

int	render(void *param)
{
	t_mlx		*mlx = param;
	t_window	*win = mlx->win_list;
	int			x, y;
	static int	offset = 0;

	if (!win || !win->pixel_buffer)
		return (1);
	for (y = 0; y < win->height; y++)
	{
		for (x = 0; x < win->width; x++)
		{
			int r = (x + offset) & 0xFF;
			int g = (y + offset) & 0xFF;
			int b = (x + y) & 0xFF;
			int color = (0xFF << 24) | (r << 16) | (g << 8) | b;
			mlx_pixel_put(mlx, win, x, y, color);
		}
	}
	offset++;
	return (0);
}

int	main(void)
{
	t_mlx		*mlx;
	t_window	*win;

	mlx = mlx_init();
	if (!mlx)
		return (1);
	win = mlx_new_window(mlx, 800, 600, "Test");
	if (!win)
	{
		free(mlx);
		return (1);
	}
	mlx_hook(win, DestroyNotify, 0, on_destroy, mlx);
	mlx_hook(win, KeyPress, KeyPressMask, on_keypress, mlx);
	mlx_loop_hook(mlx, render, mlx);
	mlx_loop(mlx);
	mlx_destroy_window(mlx, win);
	mlx_destroy_display(mlx);
	free(mlx);
	return (0);
}
