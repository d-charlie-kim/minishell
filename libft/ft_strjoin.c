/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 04:28:48 by jaejeong          #+#    #+#             */
/*   Updated: 2021/07/06 17:45:58 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*jstr;
	char	*ret;

	jstr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
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
