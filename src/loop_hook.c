/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 22:38:15 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/14 22:38:34 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

int	mlx_loop_hook(t_mlx *mlx, int (*fn)(void *), void *param)
{
	mlx->loop_hook = fn;
	mlx->loop_param = param;
	return (0);
}
