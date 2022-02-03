/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 12:09:31 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/03 14:33:45 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

static void	execute_program(t_info *info, t_process *cur_process)
{
	// if (!ft_strncmp("cd", cur_process->instruction, 3))          // together
	// 	mini_cd(info, cur_process);
	// else if (!ft_strncmp("exit", cur_process->instruction, 5))   // char
	// 	mini_exit(info, cur_process);
	// else if (!ft_strncmp("env", cur_process->instruction, 4))    // char
	// 	mini_env(info, cur_process);
	if (!ft_strncmp("export", cur_process->instruction, 7)) // char
		mini_export(info, cur_process);
	// else if (!ft_strncmp("unset", cur_process->instruction, 6)) // char
	// 	mini_unset(info, cur_process);
	else if (!ft_strncmp("pwd", cur_process->instruction, 4))   // jae
	 	mini_pwd(info, cur_process);
	// else if (!ft_strncmp("echo", cur_process->instruction, 5))  // together
	// 	mini_echo(info, cur_process);
	else
		find_instruction(info, cur_process); // 명령어가 빈 문자열일 때 아직 처리하지 못함 // jae
											 // ex) echo a | $rtjkgsrgsrth
	print_error_and_exit("명령어를 못찾았어요 ㅠㅠ\n", 5555555);
}

static bool	make_pipe_and_fork(t_process *processes, t_process **cur_process,
			int child_index, int *exit_status)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid > 0)
	{
		close(STDIN_FILENO);
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		waitpid(pid, exit_status, 0);
		return (false);
	}
	else
	{
		close(STDOUT_FILENO);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		*cur_process = &processes[child_index];
		return (true);
	}
}

static void	print_result(int exit_status)
{
	char	*buf;

	while (get_next_line(STDIN_FILENO, &buf) > 0)
	{
		write(STDOUT_FILENO, buf, ft_strlen(buf));
		write(STDOUT_FILENO, "\n", 1);
	}
	exit(exit_status);
}

static void	fork_num_of_inst(t_info *info, t_process *processes)
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
		can_fork = make_pipe_and_fork(processes, &cur_process, child_index, &exit_status);
		child_index--;
	}
	if (cur_process)
		execute_program(info, cur_process);
	print_result(exit_status);
}

void	fork_main(t_info *info, t_process *processes)
{
	int		exit_status;
	pid_t	printer_pid;

	exit_status = 0;
	printer_pid = fork();
	if (printer_pid > 0)
		waitpid(printer_pid, &exit_status, 0);
	else
		fork_num_of_inst(info, processes);
	info->last_exit_status = exit_status;
}
