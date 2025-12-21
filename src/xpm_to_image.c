/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_to_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 14:07:42 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/21 12:09:51 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mlx.h"

#define CPP2_LUT_SIZE 65536

typedef struct s_xpm_ctx {
	char		**data;
	uint32_t	*colors;
	int			w;
	int			h;
	int			num_col;
	int			cpp;
	uint32_t	fast_lut[256];
	uint32_t	*big_lut;
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
	if (sscanf(str, "%2x%2x%2x", &r, &g, &b) == 3)
		return (0xFF000000 | (r << 16) | (g << 8) | b);
	return (0xFF000000);
}

static int	build_color_table(t_xpm_ctx *ctx)
{
	int			i;
	char		*line;
	char		*col_start;
	uint32_t	color_val;
	int			idx;

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
		if (ctx->cpp == 2)
		{
			idx = ((unsigned char)line[0] << 8) | (unsigned char)line[1];
			if (idx < CPP2_LUT_SIZE)
			ctx->big_lut[idx] = color_val;
		}
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
	int		idx;

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
			else if (ctx->cpp == 2)
			{
				idx = ((unsigned char)line[x * 2] << 8)
					| (unsigned char)line[x * 2 + 1];
				buffer[y * ctx->w + x] = ctx->big_lut[idx];
			}
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
	memset(&ctx, 0, sizeof(t_xpm_ctx));
	if (sscanf(xpm_data[0], "%d %d %d %d", &ctx.w, &ctx.h, &ctx.num_col,
			&ctx.cpp) != 4)
		return (NULL);
	ctx.data = xpm_data;
	if (ctx.cpp == 2)
	{
		ctx.big_lut = calloc(CPP2_LUT_SIZE, sizeof(uint32_t));
		if (!ctx.big_lut)
			return (NULL);
	}
	img = mlx_new_image(mlx, ctx.w, ctx.h);
	if (!img)
	{
		if (ctx.big_lut)
			free(ctx.big_lut);
		return (NULL);
	}
	if (!build_color_table(&ctx))
	{
		mlx_destroy_image(mlx, img);
		if (ctx.big_lut)
			free(ctx.big_lut);
		return (NULL);
	}
	fill_texture(&ctx, img->buffer);
	if (ctx.big_lut)
		free(ctx.big_lut);
	if (width)
		*width = ctx.w;
	if (height)
		*height = ctx.h;
	return (img);
}
