/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:20:36 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/01 15:26:22 by smamalig         ###   ########.fr       */
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
