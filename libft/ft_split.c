/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 04:28:48 by jaejeong          #+#    #+#             */
/*   Updated: 2021/07/06 20:17:07 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	strnum_check(char const *s, char c)
{
	int		i;
	size_t	strnum;

	i = 0;
	strnum = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			return (strnum);
		while (s[i] && s[i] != c)
			i++;
		strnum++;
	}
	return (strnum);
}

static char	*n_str_check(char *n_str, char c, size_t *n_strlen)
{
	char	*ret_str;

	n_str += *n_strlen;
	while (*n_str == c)
		n_str++;
	ret_str = n_str;
	*n_strlen = 0;
	while (*n_str && *n_str != c)
	{
		n_str++;
		*n_strlen += 1;
	}
	return (ret_str);
}

static char	**mlc_free(char **ret)
{
	size_t	i;

	i = 0;
	while (ret[i])
	{
		free(ret[i]);
		i++;
	}
	free(ret);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	strnum;
	size_t	n_strlen;
	size_t	i;
	char	**ret;
	char	*n_str;

	if (!s)
		return (NULL);
	strnum = strnum_check(s, c);
	ret = (char **)malloc(sizeof(char *) * (strnum + 1));
	if (!ret)
		return (NULL);
	n_str = (char *)s;
	n_strlen = 0;
	i = -1;
	while (++i < strnum)
	{
		n_str = n_str_check(n_str, c, &n_strlen);
		ret[i] = (char *)malloc(sizeof(char) * n_strlen + 1);
		if (!ret)
			return (mlc_free(ret));
		ft_strlcpy(ret[i], n_str, n_strlen + 1);
	}
	ret[i] = NULL;
	return (ret);
}
