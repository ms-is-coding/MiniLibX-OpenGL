/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 03:02:28 by smamalig          #+#    #+#             */
/*   Updated: 2025/05/10 18:35:10 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_opengl.h"

static inline GLubyte	color_r(uint32_t c)
{
	return ((c >> 16) & 0xff);
}

static inline GLubyte	color_g(uint32_t c)
{
	return ((c >> 8) & 0xff);
}

static inline GLubyte	color_b(uint32_t c)
{
	return (c & 0xff);
}

static inline GLubyte	color_a(uint32_t c)
{
	return ((c >> 24) & 0xff);
}

int	mlx_pixel_put(t_mlx *mlx, void *win, int x, int y, uint32_t c)
{
	(void)win;
	(void)mlx;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 600, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glBegin(GL_POINTS);
	glColor4ub(color_r(c), color_g(c), color_b(c), color_a(c));
	glVertex2i(x, y);
	glEnd();
	return (0);
}
