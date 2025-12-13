/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:14:47 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/13 20:59:32 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "mlx.h"

typedef struct s_app {
	t_mlx		*mlx;
	t_window	*window;
	void		*sprite;
	int			img_w;
	int			img_h;
}	t_app;

int	on_destroy(void *param)
{
	mlx_loop_end(((t_app *)param)->mlx);
	return (0);
}

int	on_keypress(const int keysim, void *param)
{
	if (keysim == XK_Escape)
		mlx_loop_end(((t_app *)param)->mlx);
	return (0);
}

void	init_sprite(t_app *app)
{
	app->sprite = mlx_xpm_file_to_image(app->mlx, "player.xpm",
			&app->img_w, &app->img_h);
	if (!app->sprite)
	{
		printf("Critical Error: Could not load 'player.xpm'.\n");
		printf("Make sure the file exists in the execution directory.\n");
		mlx_destroy_window(app->mlx, app->window);
		mlx_destroy_display(app->mlx);
		free(app->mlx);
		exit(1);
	}
	printf("Success: Image loaded (%dx%d pixels)\n", app->img_w, app->img_h);
}

int	render(void *param)
{
	t_app	*app;
	int		mx;
	int		my;

	app = (t_app *)param;
	mlx_clear_window(app->mlx, app->window);
	mlx_mouse_get_pos(app->mlx, app->window, &mx, &my);
	mlx_put_image_to_window(app->mlx, app->window, app->sprite,
		mx - (app->img_w / 2),
		my - (app->img_h / 2));
	return (0);
}

int	main(void)
{
	t_app	app;

	app.mlx = mlx_init();
	if (!app.mlx)
		return (1);
	app.window = mlx_new_window(app.mlx, 800, 600, "XPM Loader Test");
	if (!app.window)
	{
		free(app.mlx);
		return (1);
	}
	init_sprite(&app);
	mlx_hook(app.window, DestroyNotify, 0, on_destroy, &app);
	mlx_hook(app.window, KeyPress, KeyPressMask, on_keypress, &app);
	mlx_loop_hook(app.mlx, render, &app);
	mlx_loop(app.mlx);
	mlx_destroy_image(app.mlx, app.sprite);
	mlx_destroy_window(app.mlx, app.window);
	mlx_destroy_display(app.mlx);
	free(app.mlx);
	return (0);
}
