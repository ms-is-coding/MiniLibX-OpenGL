/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_to_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 14:07:42 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/20 20:24:15 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

#include "mlx.h"

typedef struct s_xpm_ctx {
	char		**data;
	uint32_t	*colors;
	int			w;
	int			h;
	int			num_col;
	int			cpp;
	uint32_t	fast_lut[256];
}	t_xpm_ctx;

static uint32_t	parse_color(const char *str)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	if (!str)
		return (0xFF000000);
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '#')
		str++;
	if (strncasecmp(str, "None", 4) == 0)
		return (0x00000000);
	if (sscanf(str, "%02x%02x%02x", &r, &g, &b) == 3)
		return (0xFF000000 | (r << 16) | (g << 8) | b);
	return (0xFF000000);
}

static int	build_color_table(t_xpm_ctx *ctx)
{
	int			i;
	char		*line;
	char		*col_start;
	uint32_t	color_val;

	if (ctx->cpp > 2)
		return (0);
	i = 0;
	while (i < ctx->num_col)
	{
		line = ctx->data[i + 1];
		col_start = strstr(line, "c ");
		if (!col_start)
			return (0);
		color_val = parse_color(col_start + 2);
		if (ctx->cpp == 1)
			ctx->fast_lut[(unsigned char)line[0]] = color_val;
		i++;
	}
	return (1);
}

static void	fill_texture(t_xpm_ctx *ctx, int *buffer)
{
	int		data_offset;
	int		x;
	int		y;
	char	*line;

	data_offset = 1 + ctx->num_col;
	y = 0;
	while (y < ctx->h)
	{
		line = ctx->data[data_offset + y];
		x = 0;
		while (x < ctx->w)
		{
			if (ctx->cpp == 1)
				buffer[y * ctx->w + x] = ctx->fast_lut[(unsigned int)line[x]];
			else
				buffer[y * ctx->w + x] = 0xFFFF00FF;
			x++;
		}
		y++;
	}
}

void	*mlx_xpm_to_image(t_mlx *mlx, char **xpm_data, int *width, int *height)
{
	t_img		*img;
	t_xpm_ctx	ctx;

	if (!mlx || !xpm_data)
		return (NULL);
	if (sscanf(xpm_data[0], "%d %d %d %d", &ctx.w, &ctx.h, &ctx.num_col,
		&ctx.cpp) != 4)
		return (NULL);
	ctx.data = xpm_data;
	img = mlx_new_image(mlx, ctx.w, ctx.h);
	if (!img)
		return (NULL);
	if (!build_color_table(&ctx))
	{
		mlx_destroy_image(mlx, img);
		return (NULL);
	}
	fill_texture(&ctx, img->buffer);
	if (width)
		*width = ctx.w;
	if (height)
		*height = ctx.h;
	return (img);
}
