/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 04:44:06 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/08 04:45:35 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

int	check_quotes(char c, int flag)
{
	if (flag == 0 && c == '"')
		flag = 1;
	else if (flag == 0 && c == '\'')
		flag = 2;
	else if (flag == 1 && c == '"')
		flag = 0;
	else if (flag == 2 && c == '\'')
		flag = 0;
	return (flag);
}

void	ft_putncpy(char **dest, char *src, int index, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		*dest[i] = src[index];
		i++;
		index++;
	}
	*dest[size] = '\0';
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}
