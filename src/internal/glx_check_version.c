/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glx_check_version.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:22:57 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/13 20:07:38 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "mlx_internal.h"

int	__mlx_glx_check_version(t_mlx *mlx)
{
	GLint	maj;
	GLint	min;

	glXQueryVersion(mlx->dpy, &maj, &min);
	if (maj <= 1 && min < 2)
	{
		printf("GLX 1.2 or greater is required.\n");
		XCloseDisplay(mlx->dpy);
		free(mlx);
		return (1);
	}
	return (0);
}
