/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_file_to_image.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:47:59 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/13 19:43:18 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "mlx.h"

#define BUFF_SIZE 4096

typedef struct s_xpm_col {
	char		*str_code;
	uint32_t	color;
	char		padding[4];
}	t_xpm_col;

typedef struct s_xpm_ctx {
	char		*data;
	t_xpm_col	*colors;
	size_t		len;
	size_t		pos;
	int32_t		w;
	int32_t		h;
	int32_t		num_col;
	int32_t		cpp;
	uint32_t	lut_fast[256];
}	t_xpm_ctx;

static uint32_t	parse_hex_color(const char *str)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	if (!str)
		return (0xFF000000);
	if (str[0] == '#')
		str++;
	if (strlen(str) < 6)
		return (0xFF000000);
	sscanf(str, "%02x%02x%02x", &r, &g, &b);
	return (0xFF000000 | (r << 16) | (g << 8) | b);
}

static char	*get_next_quote(t_xpm_ctx *ctx)
{
	char	*start;
	size_t	i;

	while (ctx->pos < ctx->len && ctx->data[ctx->pos] != '"')
		ctx->pos++;
	if (ctx->pos >= ctx->len)
		return (NULL);
	ctx->pos++;
	start = &ctx->data[ctx->pos];
	i = 0;
	while (ctx->pos + i < ctx->len && ctx->data[ctx->pos + i] != '"')
		i++;
	if (ctx->pos + i >= ctx->len)
		return (NULL);
	ctx->data[ctx->pos + i] = '\0';
	ctx->pos += i + 1;
	return (start);
}

static int	load_file_content(const char *filename, t_xpm_ctx *ctx)
{
	int		fd;
	char	buffer[BUFF_SIZE];
	ssize_t	ret;
	char	*new_data;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	ctx->data = NULL;
	ctx->len = 0;
	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		new_data = realloc(ctx->data, ctx->len + ret + 1);
		if (!new_data)
		{
			free(ctx->data);
			close(fd);
			return (0);
		}
		ctx->data = new_data;
		memcpy(ctx->data + ctx->len, buffer, ret);
		ctx->len += ret;
	}
	if (ctx->data)
		ctx->data[ctx->len] = '\0';
	close(fd);
	return (ctx->data != NULL);
}

static void	parse_colors(t_xpm_ctx *ctx)
{
	int		i;
	char	*line;
	char	*color_start;

	memset(ctx->lut_fast, 0, sizeof(uint32_t) * 256);
	i = 0;
	while (i < ctx->num_col)
	{
		line = get_next_quote(ctx);
		if (!line)
			break ;
		color_start = strstr(line + ctx->cpp, "c ");
		if (color_start)
		{
			color_start += 2;
			while (*color_start == ' ')
				color_start++;
			uint32_t final_col;
			if (strncasecmp(color_start, "None", 4) == 0)
				final_col = 0x00000000;
			else
				final_col = parse_hex_color(color_start);
			if (ctx->cpp == 1)
				ctx->lut_fast[(unsigned char)line[0]] = final_col;
			else
			{
				ctx->colors[i].str_code = strndup(line, ctx->cpp);
				ctx->colors[i].color = final_col;
			}
		}
		i++;
	}
}

static uint32_t	get_pixel_color(t_xpm_ctx *ctx, char *ptr)
{
	int	i;

	if (ctx->cpp == 1)
		return (ctx->lut_fast[(unsigned char)*ptr]);
	i = 0;
	while (i < ctx->num_col)
	{
		if (strncmp(ptr, ctx->colors[i].str_code, ctx->cpp) == 0)
			return (ctx->colors[i].color);
		i++;
	}
	return (0xFF000000);
}

static void	fill_image_data(t_xpm_ctx *ctx, t_img *img)
{
	int		x;
	int		y;
	char	*line;
	int		pixel_idx;

	pixel_idx = 0;
	y = 0;
	while (y < ctx->h)
	{
		line = get_next_quote(ctx);
		if (!line)
			break ;
		x = 0;
		while (x < ctx->w)
		{
			img->buffer[pixel_idx] = (int)get_pixel_color(ctx,
				line + (x * ctx->cpp));
			pixel_idx++;
			x++;
		}
		y++;
	}
}

void	*mlx_xpm_file_to_image(t_mlx *mlx, char *filename,
			int *width, int *height)
{
	t_xpm_ctx	ctx;
	t_img		*img;
	char		*header;

	memset(&ctx, 0, sizeof(t_xpm_ctx));
	if (!load_file_content(filename, &ctx))
		return (NULL);
	header = get_next_quote(&ctx);
	if (header && sscanf(header, "%d %d %d %d", &ctx.w, &ctx.h, &ctx.num_col, &ctx.cpp) != 4)
	{
		header = get_next_quote(&ctx);
		sscanf(header, "%d %d %d %d", &ctx.w, &ctx.h, &ctx.num_col, &ctx.cpp);
	}
	if (ctx.cpp > 1)
		ctx.colors = calloc(ctx.num_col, sizeof(t_xpm_col));
	img = mlx_new_image(mlx, ctx.w, ctx.h);
	if (img)
	{
		parse_colors(&ctx);
		fill_image_data(&ctx, img);
		if (width) *width = ctx.w;
		if (height) *height = ctx.h;
	}
	if (ctx.colors)
	{
		for (int i = 0; i < ctx.num_col; i++)
			free(ctx.colors[i].str_code);
		free(ctx.colors);
	}
	free(ctx.data);
	return (img);
}
