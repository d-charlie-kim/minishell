/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 19:32:38 by jaejeong          #+#    #+#             */
/*   Updated: 2021/07/06 17:46:30 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (big[i + j] == little[j] || little[j] == '\0')
			{
				if (i + j > len)
					return (0);
				if (little[j] == '\0')
					return ((char *)&big[i]);
				j++;
			}
		}
		i++;
	}
	return (0);
}
