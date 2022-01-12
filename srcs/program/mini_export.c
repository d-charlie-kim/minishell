/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:19:39 by dokkim            #+#    #+#             */
/*   Updated: 2022/01/12 14:12:24 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

void	print_export(t_env *env)
{
	t_env	*temp;

	temp = env;
}

int	mini_export(t_info *info, t_process *process)
{
	if (!process->arguments)
	{
		print_export(info->env);
	}
}

// 정렬을 먼저 해준 뒤에 (= 새로운 t_env 를 하나 만들어주고)
// declare -x 포함해서 출력을 한다.
// 아니면 정렬을 해주면서 