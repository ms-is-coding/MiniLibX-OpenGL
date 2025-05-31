/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autorepeat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:59:28 by smamalig          #+#    #+#             */
/*   Updated: 2025/05/31 20:00:01 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_opengl.h"

int	mlx_do_key_autorepeatoff(t_mlx *mlx)
{
	XAutoRepeatOff(mlx->dpy);
	return (0);
}

int	mlx_do_key_autorepeaton(t_mlx *mlx)
{
	XAutoRepeatOn(mlx->dpy);
	return (0);
}
