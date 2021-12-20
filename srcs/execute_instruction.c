/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_instruction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 12:09:31 by jaejeong          #+#    #+#             */
/*   Updated: 2021/12/20 16:51:10 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

static int	start_program(t_info *info, t_process *cur_process)
{
	if (!ft_strncmp("cd", cur_process->instruction, 3))
		mini_cd(info, cur_process);
	else if (!ft_strncmp("exit", cur_process->instruction, 5))
		mini_exit(info, cur_process);
	else if (!ft_strncmp("env", cur_process->instruction, 4))
		mini_env(info, cur_process);
	else if (!ft_strncmp("export", cur_process->instruction, 7))
		mini_export(info, cur_process);
	else if (!ft_strncmp("unset", cur_process->instruction, 6))
		mini_unset(info, cur_process);
	else if (!ft_strncmp("pwd", cur_process->instruction, 4))
		mini_pwd(info, cur_process);
	else if (!ft_strncmp("echo", cur_process->instruction, 5))
		mini_echo(info, cur_process);
	else
		find_instruction(info, cur_process); // path, 상대경로, 절대경로에서 찾아서 사용
	print_errer_and_exit(); // 명령어를 찾지 못했다는 메세지와 종료. 종료코드 뭐지..?
}

static bool	make_pipe_and_fork(t_process *processes, t_process *cur_process,
			int child_index, int *exit_status)
{
	int		status;
	int		pipefd[2];
	pid_t	pid;

	pipe(pipefd[2]);
	pid = fork();
	if (pid > 0)
	{
		close(STDIN_FILENO);
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		waitpid(pid, &status, 0);
		return (false);
	}
	else
	{
		close(STDOUT_FILENO);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		cur_process = &processes[child_index];
		return (true);
	}
}

static void	execute_instruction(t_info *info, t_process *processes)
// 생각해보니 minishell 프로세스의 표준입력을 닫아버리면 안됨 ㅡㅡ
//	구조 다시 생각해보기
{
	int			child_index;
	int			exit_status;
	bool		can_fork;
	t_process	*cur_process;

	child_index = info->process_count - 1;
	cur_process = NULL;
	can_fork = true;
	while (child_index >= 0)
	{
		if (!can_fork)
			break ;
		can_fork = make_pipe_and_fork(processes, cur_process, child_index, &exit_status);
		child_index--;
	}
	if (cur_process)
		start_program(info, cur_process);
	exit(exit_status);
}

void	execute_instruction_main(t_info *info, t_process *processes)
{
	pid_t	printer_pid;
	int		exit_status;

	printer_pid = fork();
	if (printer_pid > 0)
		waitpid(printer_pid, &exit_status, 0);
	else
		execute_instruction(info, processes);
	info->last_exit_status = exit_status;
}
