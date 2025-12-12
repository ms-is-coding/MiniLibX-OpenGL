/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:25:26 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/12 14:31:46 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "mlx.h"

int	mlx_clear_window(t_mlx *mlx, t_window *win)
{
	(void)mlx;
	if (!win || !win->pixel_buffer)
		return (0);
	memset(win->pixel_buffer, 0, win->width * win->height * sizeof(int));
	return (0);
}
