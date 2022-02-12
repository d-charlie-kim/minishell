/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 23:30:22 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/12 22:42:42 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"

bool	is_builtin_function(t_process *cur_process)
{
	if ((!ft_strncmp("cd", cur_process->instruction, 3)) ||\
		(!ft_strncmp("exit", cur_process->instruction, 5)) ||\
		(!ft_strncmp("env", cur_process->instruction, 4)) ||\
		(!ft_strncmp("export", cur_process->instruction, 7)) ||\
		(!ft_strncmp("unset", cur_process->instruction, 6)) ||\
		(!ft_strncmp("pwd", cur_process->instruction, 4)) ||\
		(!ft_strncmp("echo", cur_process->instruction, 5)))
		return (true);
	else
		return (false);
}

int	execute_program(t_info *info, t_process *cur_process)
{
	if (!cur_process->instruction)
		return (exit_process(info, info->last_exit_status));
	if (!ft_strncmp("cd", cur_process->instruction, 3))
		return (mini_cd(info, cur_process));
	else if (!ft_strncmp("exit", cur_process->instruction, 5))
		return (mini_exit(info, cur_process));
	else if (!ft_strncmp("env", cur_process->instruction, 4))
		return (mini_env(info, cur_process));
	else if (!ft_strncmp("export", cur_process->instruction, 7))
		return (mini_export(info, cur_process));
	else if (!ft_strncmp("unset", cur_process->instruction, 6))
		return (mini_unset(info, cur_process));
	else if (!ft_strncmp("pwd", cur_process->instruction, 4))
		return (mini_pwd(info, cur_process));
	else if (!ft_strncmp("echo", cur_process->instruction, 5))
		return (mini_echo(info, cur_process));
	else
		return (find_instruction(info, cur_process));
	print_error_and_exit("명령어를 찾지 못했어요ㅠㅠ\n", 5555555);
}
