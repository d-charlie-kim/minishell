/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:38:50 by jaejeong          #+#    #+#             */
/*   Updated: 2021/07/06 17:43:42 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	ngtv;
	int	num;

	i = 0;
	ngtv = 0;
	num = 0;
	while ((9 <= nptr[i] && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		ngtv = 1;
		i++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		num *= 10;
		num += nptr[i] - 48;
		i++;
	}
	if (ngtv == 1)
		num *= -1;
	return (num);
}
