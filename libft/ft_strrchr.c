/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 17:04:49 by jaejeong          #+#    #+#             */
/*   Updated: 2021/07/06 17:46:34 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*s)
	{
		s++;
		i++;
	}
	if (c == 0)
		return ((char *)s);
	s--;
	i--;
	while (i >= 0)
	{
		if (*s == c)
			return ((char *)s);
		i--;
		s--;
	}
	return (0);
}
