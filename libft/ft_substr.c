/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 04:28:48 by jaejeong          #+#    #+#             */
/*   Updated: 2021/07/06 17:58:07 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	mlc_size;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
	{
		subs = (char *)malloc(sizeof(char));
		if (!subs)
			return (NULL);
		*subs = '\0';
		return (subs);
	}
	mlc_size = sizeof(char) * len + 1;
	if (ft_strlen(s) <= (size_t)start + len)
		mlc_size = sizeof(char) * (ft_strlen(s) - start + 1);
	subs = (char *)malloc(mlc_size);
	if (!subs)
		return (NULL);
	ft_strlcpy(subs, (s + start), mlc_size);
	return (subs);
}
