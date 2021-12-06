/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 04:28:48 by jaejeong          #+#    #+#             */
/*   Updated: 2021/07/06 17:44:23 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	input_pos(char *temp, int n, int *neg)
{
	int	i;

	*neg = 0;
	if (n == 0)
	{
		*temp = '0';
		return (1);
	}
	i = 0;
	while (n != 0)
	{
		*temp++ = n % 10 + 48;
		n /= 10;
		i++;
	}
	return (i);
}

static int	input_neg(char *temp, int n, int *neg)
{
	int	i;

	*neg = 1;
	i = 0;
	while (n != 0)
	{
		*temp++ = n % 10 * (-1) + 48;
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	temp[12];
	char	*arr;
	char	*ret;
	int		len;
	int		neg;

	if (n >= 0)
	{
		len = input_pos(temp, n, &neg);
		arr = (char *)malloc(sizeof(char) * len + 1);
	}
	if (n < 0)
	{
		len = input_neg(temp, n, &neg);
		arr = (char *)malloc(sizeof(char) * len + 2);
	}
	if (!arr)
		return (NULL);
	ret = arr;
	if (neg == 1)
		*arr++ = '-';
	while (0 <= --len)
		*arr++ = temp[len];
	*arr = '\0';
	return (ret);
}
