/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 18:06:47 by jaejeong          #+#    #+#             */
/*   Updated: 2021/07/06 17:46:03 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	s_len;

	s_len = ft_strlen(src);
	i = 0;
	j = 0;
	while (*dst && i < size)
	{
		dst++;
		i++;
	}
	while (*dst)
		dst++;
	while (*src && (i + j + 1) < size)
	{
		*dst++ = *src++;
		j++;
	}
	*dst = '\0';
	return (i + s_len);
}
