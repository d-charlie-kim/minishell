/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 23:30:22 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/19 23:29:06 by jaejeong         ###   ########.fr       */
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

static int	check_file_is_exist(t_list *redirect)
{
	int				fd;
	t_redirect_pair	*pair;

	while (redirect)
	{
		pair = (t_redirect_pair *)(redirect->content);
		if (pair->symbol == SINGLE_IN)
		{
			fd = open(pair->file_name, 0);
			if (fd < 0)
			{
				ft_putstr_fd("bash: ", STDERR_FILENO);
				ft_putstr_fd(pair->file_name, STDERR_FILENO);
				ft_putstr_fd(": ", STDERR_FILENO);
				ft_putstr_fd(strerror(ENOENT), STDERR_FILENO);
				ft_putchar_fd('\n', STDERR_FILENO);
				return (-1);
			}
			close(fd);
		}
		redirect = redirect->next;
	}
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
	if (check_file_is_exist(process->redirect) == -1)
		return (ENOENT);
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
