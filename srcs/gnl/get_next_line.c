/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:18:40 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/19 14:34:17 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	zero_ret(char **line, char *temp)
{
	if (!temp)
	{
		*line = (char *)malloc(sizeof(char) * 1);
		if (!*line)
			return (-1);
		**line = '\0';
	}
	else
	{
		*line = (char *)malloc(sizeof(char) * (ft_strlen(temp) + 1));
		if (!*line)
		{
			free(temp);
			return (-1);
		}
		ft_strlcpy(*line, temp, ft_strlen(temp) + 1);
		free(temp);
	}
	return (0);
}

static int	one_ret(char **line, char **save, char *temp)
{
	int	new;
	int	null;

	new = 0;
	null = 0;
	while (temp[new] != '\n')
		new++;
	while (temp[null] != '\0')
		null++;
	*line = (char *)malloc(sizeof(char) * (new + 1));
	if (!*line)
		return (error_free(temp, NULL));
	*save = (char *)malloc(sizeof(char) * (null - new));
	if (!*save)
		return (error_free(temp, *line));
	ft_strlcpy(*line, temp, new + 1);
	ft_strlcpy(*save, temp + new + 1, null - new);
	free(temp);
	return (1);
}

static char	*add_temp(char **temp, char *buf)
{
	char	*p;

	p = *temp;
	*temp = ft_strjoin(*temp, buf);
	free(p);
	if (!*temp)
		return (NULL);
	return (*temp);
}

static int	read_buf(char *buf, char **temp, int fd)
{
	ssize_t	read_ret;

	read_ret = read(fd, buf, BUFFER_SIZE);
	if (!read_ret)
		return (0);
	if (read_ret < 0)
	{
		if (*temp)
			free(*temp);
		return (-1);
	}
	buf[read_ret] = '\0';
	if (!*temp)
	{
		*temp = (char *)malloc(sizeof(char) * (read_ret + 1));
		ft_strlcpy(*temp, buf, read_ret + 1);
	}
	else
		*temp = add_temp(temp, buf);
	if (!*temp)
		return (-1);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	char		*temp;
	static char	*save[OPEN_MAX];
	int			ret;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	temp = NULL;
	if (save[fd])
	{
		temp = (char *)malloc(sizeof(char) * (ft_strlen(save[fd]) + 1));
		if (!temp)
			return (-1);
		ft_strlcpy(temp, save[fd], ft_strlen(save[fd]) + 1);
		free(save[fd]);
		save[fd] = NULL;
	}
	while (!newline_check(temp))
	{
		ret = read_buf(buf, &temp, fd);
		if (ret == 0 || ret == -1)
			return (zero_or_error(line, temp, ret));
	}
	return (one_ret(line, &save[fd], temp));
}
