/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 14:29:26 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/19 14:46:35 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	zero_or_error(char **line, char *temp, int ret)
{
	if (ret == 0)
		return (zero_ret(line, temp));
	else if (ret == -1)
		return (-1);
	return (0);
}

int	error_free(char *first, char *second)
{
	free (first);
	free (second);
	return (-1);
}
