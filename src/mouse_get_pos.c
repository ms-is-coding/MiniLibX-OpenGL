/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_get_pos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:54:16 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/12 07:10:18 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

int	mlx_mouse_get_pos(t_mlx *mlx, t_window *win, int *x_ptr, int *y_ptr)
{
	Window			root;
	Window			child;
	int				root_x;
	int				root_y;
	unsigned int	mask;

	return (XQueryPointer(mlx->dpy, win->xwin, &root, &child,
			&root_x, &root_y, x_ptr, y_ptr, &mask));
}
