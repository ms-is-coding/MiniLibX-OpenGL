/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:25:35 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/13 20:07:47 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlx_internal.h"

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
