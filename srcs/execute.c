/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 23:30:22 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/19 20:03:29 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"

bool	is_builtin_function(t_process *cur_process)
{
	if ((!cur_process->instruction) || \
		(!ft_strncmp("cd", cur_process->instruction, 3)) || \
		(!ft_strncmp("exit", cur_process->instruction, 5)) || \
		(!ft_strncmp("env", cur_process->instruction, 4)) || \
		(!ft_strncmp("export", cur_process->instruction, 7)) || \
		(!ft_strncmp("unset", cur_process->instruction, 6)) || \
		(!ft_strncmp("pwd", cur_process->instruction, 4)) || \
		(!ft_strncmp("echo", cur_process->instruction, 5)))
		return (true);
	else
		return (false);
}

int	execute_program(t_info *info, t_process *cur_process)
{
	if (!cur_process->instruction)
		return (exit_process(info, cur_process, info->last_exit_status));
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
		find_instruction(info, cur_process);
	return (0);
}

int	execute_single_builtin(t_info *info, t_process *process)
// mac 환경에서 파이프 누수 테스트 해볼 것
{
	int	ret;
	int	save_stdin;
	int	save_stdout;

	ret = 0;
	(void)info;
	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	set_input_redirect(process);
	set_output_redirect(process);
	ret = execute_program(info, process);
	dup2(save_stdin, STDIN_FILENO);
	close(save_stdin);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdout);
	return (ret);
}
