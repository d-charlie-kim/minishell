/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 04:28:48 by jaejeong          #+#    #+#             */
/*   Updated: 2021/07/06 19:59:19 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	begin_size_check(char const *s1, char const *set)
{
	size_t	ret;

	ret = 0;
	while (*s1 && ft_strchr(set, *s1))
	{
		ret++;
		s1++;
	}
	return (ret);
}

static	size_t	end_size_check(char const *s1, char const *set)
{
	size_t	ret;

	ret = 0;
	while (*(s1 + 1))
		s1++;
	while (ft_strchr(set, *s1--))
		ret++;
	return (ret);
}

static	char	*make_empty_str(void)
{
	char	*str;

	str = ft_strdup("");
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		index;
	size_t	begin_size;
	size_t	end_size;
	size_t	ret_size;
	char	*ret;

	begin_size = begin_size_check(s1, set);
	end_size = end_size_check(s1, set);
	if (begin_size == ft_strlen(s1))
		return (make_empty_str());
	ret_size = ft_strlen(s1) - begin_size - end_size + 1;
	ret = (char *)malloc(sizeof(char) * ret_size);
	if (!ret)
		return (NULL);
	while (0 < begin_size--)
		s1++;
	index = 0;
	while (1 < ret_size--)
		ret[index++] = *s1++;
	ret[index] = '\0';
	return (ret);
}
