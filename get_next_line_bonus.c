/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakherra <aakherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:58:25 by aakherra          #+#    #+#             */
/*   Updated: 2024/11/26 08:11:23 by aakherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*check_reminder(char **buf, char **rb)
{
	char	*line;

	line = NULL;
	if (*buf && **buf)
		line = ft_strdup(*buf);
	free(*rb);
	free(*buf);
	*rb = NULL;
	*buf = NULL;
	return (line);
}

char	*get_line(char **buf, char **rb)
{
	char	*r;
	char	*n;
	char	*line;

	line = NULL;
	n = ft_strchr(*buf, '\n');
	if (n)
	{
		line = ft_substr(*buf, 0, (n - *buf) + 1);
		r = ft_strdup(n + 1);
		free(*buf);
		*buf = r;
		free(*rb);
	}
	return (line);
}

void	handle_bufs(char **n, char *buf)
{
	char	*new_buf;

	if (*n)
	{
		new_buf = ft_strjoin(*n, buf);
		free(*n);
		*n = new_buf;
	}
	else
		*n = ft_strdup(buf);
}

char	*get_next_line(int fd)
{
	char					*buffer;
	char					*l;
	ssize_t					nb;
	static char				*arr[1024];

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	l = get_line(&arr[fd], &buffer);
	if (l)
		return (l);
	nb = read(fd, buffer, BUFFER_SIZE);
	while (nb > 0)
	{
		buffer[nb] = '\0';
		handle_bufs(&arr[fd], buffer);
		l = get_line(&arr[fd], &buffer);
		if (l)
			return (l);
		nb = read(fd, buffer, BUFFER_SIZE);
	}
	return (check_reminder(&arr[fd], &buffer));
}
