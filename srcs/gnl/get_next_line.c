/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:18:40 by jaejeong          #+#    #+#             */
/*   Updated: 2021/12/23 20:16:10 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		zero_ret(char **line, char *temp)
{
	if (!temp)
	{
		if (!(*line = (char *)malloc(sizeof(char) * 1)))
			return (-1);
		**line = '\0';
	}
	else
	{
		if (!(*line = (char *)malloc(sizeof(char) * (ft_strlen(temp) + 1))))
		{
			free(temp);
			return (-1);
		}
		ft_strlcpy(*line, temp, ft_strlen(temp) + 1);
		free(temp);
	}
	return (0);
}

static int		one_ret(char **line, char **save, char *temp)
{
	int			new;
	int			null;

	new = 0;
	null = 0;
	while (temp[new] != '\n')
		new++;
	while (temp[null] != '\0')
		null++;
	if (!(*line = (char *)malloc(sizeof(char) * (new + 1))))
	{
		free(temp);
		return (-1);
	}
	if (!(*save = (char *)malloc(sizeof(char) * (null - new))))
	{
		free(temp);
		free(*line);
		return (-1);
	}
	ft_strlcpy(*line, temp, new + 1);
	ft_strlcpy(*save, temp + new + 1, null - new);
	free(temp);
	return (1);
}

static char		*add_temp(char **temp, char *buf)
{
	char *p;

	p = *temp;
	*temp = ft_strjoin(*temp, buf);
	free(p);
	if (!*temp)
		return (NULL);
	return (*temp);
}

static int		read_buf(char *buf, char **temp, int fd)
{
	ssize_t		read_ret;

	if (!(read_ret = read(fd, buf, BUFFER_SIZE)))
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
		if (!(*temp = (char *)malloc(sizeof(char) * (read_ret + 1))))
			return (-1);
		ft_strlcpy(*temp, buf, read_ret + 1);
	}
	else
	{
		if (!(*temp = add_temp(temp, buf)))
			return (-1);
	}
	return (1);
}

int				get_next_line(int fd, char **line)
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
		if (!(temp = (char *)malloc(sizeof(char) * (ft_strlen(save[fd]) + 1))))
			return (-1);
		ft_strlcpy(temp, save[fd], ft_strlen(save[fd]) + 1);
		free(save[fd]);
		save[fd] = NULL;
	}
	while (!newline_check(temp))
	{
		ret = read_buf(buf, &temp, fd);
		if (ret == 0)
			return (zero_ret(line, temp));
		else if (ret == -1)
			return (-1);
	}
	return (one_ret(line, &save[fd], temp));
}
