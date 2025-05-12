/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_file_to_image.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:47:59 by smamalig          #+#    #+#             */
/*   Updated: 2025/05/10 22:39:33 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_opengl.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// void	*mlx_xpm_file_to_image(t_mlx *mlx, const char *filename,
// 	int *width, int *height)
// {
// 	int		fd;
// 	off_t	size;
// 	
// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 		return (NULL);
// 	size = lseek(fd, 0, SEEK_END);
// 	if (size == -1)
// 		return (NULL);
// 	return (0);
// }
