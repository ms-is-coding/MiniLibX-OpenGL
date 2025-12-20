/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_file_to_image.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:47:59 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/20 20:42:54 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlx.h"
#include "mlx_internal.h"

static char	*extract_next_token(char **ptr)
{
	char	*start;
	char	*curr;

	curr = *ptr;
	while (*curr && *curr != '"')
		curr++;
	if (!*curr)
		return (NULL);
	start = ++curr;
	while (*curr && *curr != '"')
		curr++;
	if (*curr == '"')
		*curr++ = '\0';
	*ptr = curr;
	return (start);
}

static int	grow_array(char ***lines, int *cap, const int count)
{
	char	**tmp;

	if (count < *cap - 1)
		return (1);
	*cap *= 2;
	tmp = realloc(*lines, sizeof(char *) * (*cap));
	if (!tmp)
		return (0);
	*lines = tmp;
	return (1);
}

static char	**tokenize_xpm_data(char *data)
{
	char	**lines;
	char	*token;
	int		cap;
	int		cnt;

	cap = 64;
	cnt = 0;
	lines = malloc(sizeof(char *) * cap);
	if (!lines || !data)
	{
		if (lines)
			free(lines);
		return (NULL);
	}
	while (1)
	{
		token = extract_next_token(&data);
		if (!token)
			break ;
		if (!grow_array(&lines, &cap, cnt))
			return (free(lines), NULL);
		lines[cnt++] = token;
	}
	lines[cnt] = NULL;
	return (lines);
}

void	*mlx_xpm_file_to_image(t_mlx *mlx, char *filename,
			int *width, int *height)
{
	char	*file_content;
	char	**xpm_data;
	void	*img;

	file_content = __mlx_read_xpm_file(filename);
	if (!file_content)
		return (NULL);
	xpm_data = tokenize_xpm_data(file_content);
	if (!xpm_data)
	{
		free(file_content);
		return (NULL);
	}
	img = mlx_xpm_to_image(mlx, xpm_data, width, height);
	free(xpm_data);
	free(file_content);
	return (img);
}
