/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:00:28 by jaejeong          #+#    #+#             */
/*   Updated: 2021/07/06 17:46:11 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
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
