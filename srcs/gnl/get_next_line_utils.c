/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:19:18 by jaejeong          #+#    #+#             */
/*   Updated: 2021/12/23 20:16:14 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			newline_check(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

size_t		ft_strlen(const char *str)
{
	size_t i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t		ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i + 1 < size && *src)
	{
		*dest++ = *src++;
		i++;
	}
	if (size != 0)
		*dest = '\0';
	while (*src != '\0')
	{
		src++;
		i++;
	}
	return (i);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*jstr;
	char	*ret;

	jstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!jstr)
		return (NULL);
	ret = jstr;
	while (*s1)
		*jstr++ = *s1++;
	while (*s2)
		*jstr++ = *s2++;
	*jstr = '\0';
	return (ret);
}
