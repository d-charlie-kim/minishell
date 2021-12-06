/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 04:28:48 by jaejeong          #+#    #+#             */
/*   Updated: 2021/07/06 19:26:11 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*n_dest;
	unsigned char	*n_src;

	if (dest == src || n == 0)
		return (dest);
	n_dest = (unsigned char *)dest;
	n_src = (unsigned char *)src;
	if (n_dest < n_src)
	{
		while (n)
		{
			*n_dest++ = *n_src++;
			n--;
		}
	}
	else
	{
		while (n)
		{
			*(n_dest + n - 1) = *(n_src + n - 1);
			n--;
		}
	}
	return (dest);
}
