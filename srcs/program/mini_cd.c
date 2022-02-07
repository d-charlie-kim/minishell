/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 19:06:37 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/07 19:49:01 by dokkim           ###   ########.fr       */
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
	else if (get_env_value("HOME"))
		ret = chdir("$HOME");
	if (ret == -1)
		print_error_and_exit();
}
