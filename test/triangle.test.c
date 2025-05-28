/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.test.c                                       ⠀⠀⠀⠀⢀⣴⣿⠟⠁ ⣿⠟⢹⣿⣿⠀   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 01:18:41 by smamalig          #+#    #+#             */
/*   Updated: 2025/05/27 15:58:47 by smamalig              ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_opengl.h"
#include <GL/gl.h>
#include <unistd.h>

int	render(void *mlx)
{
	mlx_mouse_move(mlx, NULL, 400, 300);
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(-0.5, -0.5);
	glColor3f(0, 1, 0);
	glVertex2f(0.5, -0.5);
	glColor3f(0, 0, 1);
	glVertex2f(0, 0.5);
	glEnd();
	return (0);
}

int	main(void)
{
	t_mlx	*mlx;
	void	*win;

	mlx = mlx_init();
	if (!mlx)
		return (1);
	win = mlx_new_window(mlx, 800, 600, "Test");
	if (!win)
		return (1);
	mlx_mouse_hide(mlx, win);
	mlx_mouse_show(mlx, win);
	mlx_loop_hook(mlx, render, mlx);
	mlx_loop(mlx);
	mlx_destroy_window(mlx, NULL);
	mlx_destroy_display(mlx);
	free(mlx);
	return (0);
}
