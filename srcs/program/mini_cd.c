/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 19:06:37 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/07 00:39:17 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

int	mini_cd(t_info *info, t_process *process)
{
	int	ret;

	ret = 0;
	if (process->arguments[0])
		ret = chdir(process->arguments[0]);
	else
		ret = chdir("~");
	if (ret == -1)
		print_error_and_exit();
}
