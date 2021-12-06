/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 04:28:48 by jaejeong          #+#    #+#             */
/*   Updated: 2021/07/06 19:25:49 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*n_dest;
	unsigned char	*n_src;

	n_dest = (unsigned char *)dest;
	n_src = (unsigned char *)src;
	if (!n_dest && !n_src)
		return (0);
	while (n--)
	{
		*n_dest = *n_src;
		if (*n_dest++ == (unsigned char)c)
			return (n_dest);
		n_src++;
	}
	return (NULL);
}
