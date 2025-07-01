/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:25:35 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/01 10:57:27 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>

int	__mlx_init_display(t_mlx *mlx)
{
	mlx->dpy = XOpenDisplay(NULL);
	if (!mlx->dpy)
	{
		free(mlx);
		return (1);
	}
	return (0);
}
