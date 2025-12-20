/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_xpm_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 20:35:20 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/20 20:43:48 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mlx_internal.h"

#define BUFF_SIZE 4096

static int	join_buf(char **data, size_t *len, const char *buf,
		const ssize_t ret)
{
	char	*tmp;

	tmp = realloc(*data, *len + ret + 1);
	if (!tmp)
		return (0);
	*data = tmp;
	memcpy(*data + *len, buf, ret);
	*len += ret;
	return (1);
}

static char	*read_fd_content(const int fd)
{
	char	buf[BUFF_SIZE];
	char	*data;
	size_t	len;
	ssize_t	ret;

	data = NULL;
	len = 0;
	ret = read(fd, buf, BUFF_SIZE);
	while (ret > 0)
	{
		if (!join_buf(&data, &len, buf, ret))
		{
			free(data);
			return (NULL);
		}
		ret = read(fd, buf, BUFF_SIZE);
	}
	if (data)
		data[len] = '\0';
	return (data);
}

char	*__mlx_read_xpm_file(const char *filename)
{
	int		fd;
	char	*data;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	data = read_fd_content(fd);
	close(fd);
	return (data);
}
