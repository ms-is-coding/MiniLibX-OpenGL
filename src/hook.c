/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:20:36 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/17 10:33:24 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

int	mlx_hook(t_window *win, int x_event, int x_mask, int (*fn)(), void *param)
{
	win->hooks[x_event].hook = fn;
	win->hooks[x_event].param = param;
	win->hooks[x_event].mask = x_mask;
	return (0);
}

int	mlx_key_hook(t_window *win, int (*fn)(), void *param)
{
	return (mlx_hook(win, KeyPress, KeyPressMask, fn, param));
}

int	mlx_mouse_hook(t_window *win, int (*fn)(), void *param)
{
	return (mlx_hook(win, ButtonPress, ButtonPressMask, fn, param));
}

int	mlx_expose_hook(t_window *win, int (*fn)(), void *param)
{
	return (mlx_hook(win, Expose, ExposureMask, fn, param));
}
