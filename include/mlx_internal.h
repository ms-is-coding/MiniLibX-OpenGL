/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 19:56:23 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/20 20:35:08 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_INTERNAL_H
# define MLX_INTERNAL_H

# include "mlx_types.h"

int		__mlx_glx_check_version(t_mlx *mlx);
int		__mlx_init_display(t_mlx *mlx);
int		__mlx_init_opengl(t_mlx *mlx);
int		__mlx_get_visual(t_mlx *mlx);
void	__mlx_prevent_resize(t_mlx *mlx, t_window *win, int width, int height);
char	*__mlx_read_xpm_file(const char *filename);

#endif // MLX_INTERNAL_H
