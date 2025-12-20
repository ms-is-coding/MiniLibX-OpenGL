/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 14:07:14 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/20 14:53:57 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

/**
 * @note In this OpenGL implementation, we enforce a 32-bit TrueColor visual
 * pipeline (CPU Buffer -> GL_BGRA Texture -> GPU).<br>
 * Unlike legacy X11 implementations that required mapping RGB to hardware
 * palette indices (Colormap), our architecture guarantees a direct 1:1 mapping.
 * <br>This function is intentionally a "Pass-Through" to maintain API
 * compatibility with zero CPU overhead;
 */
int	mlx_get_color_value(t_mlx *mlx, const int color)
{
	(void)mlx;
	return (color);
}
