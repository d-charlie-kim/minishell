/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 12:09:31 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/09 17:26:03 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

static void	execute_program(t_info *info, t_process *cur_process)
{
	// if (!ft_strncmp("cd", cur_process->instruction, 3))          // together
	// 	mini_cd(info, cur_process);
	if (!ft_strncmp("exit", cur_process->instruction, 5))   // char
		mini_exit();
	else if (!ft_strncmp("env", cur_process->instruction, 4))    // char
		mini_env(info, cur_process);
	else if (!ft_strncmp("export", cur_process->instruction, 7)) // char
		mini_export(info, cur_process);
	else if (!ft_strncmp("unset", cur_process->instruction, 6)) // char
		mini_unset(info, cur_process);
	else if (!ft_strncmp("pwd", cur_process->instruction, 4))   // jae
	 	mini_pwd(info, cur_process);
	else if (!ft_strncmp("echo", cur_process->instruction, 5))  // together
		mini_echo(info, cur_process);
	else
		find_instruction(info, cur_process); // 명령어가 빈 문자열일 때 아직 처리하지 못함 // jae
											 // ex) echo a | $rtjkgsrgsrth
	print_error_and_exit("명령어를 찾지 못했어요ㅠㅠ\n", 5555555);
}

static void	set_output_fd(int pipe_fd[])
{
	close(pipe_fd[0]);
	close(STDOUT_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
}

static void	set_input_fd(int pipe_fd[])
{
	close(pipe_fd[1]);
	close(STDIN_FILENO);
	dup2(pipe_fd[0], STDIN_FILENO);
}

static void	fork_recursive(t_info *info, t_process *processes, int index)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (index == 0)
		execute_program(info, &processes[index]);
	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		set_output_fd(pipe_fd);
		fork_recursive(info, processes, index - 1);
	}
	set_input_fd(pipe_fd);
	waitpid(pid, NULL, 0);
	execute_program(info, &processes[index]);
}

void	fork_main(t_info *info, t_process *processes)
{
	int		exit_status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		fork_recursive(info, processes, info->process_count - 1);
	waitpid(pid, &exit_status, 0);
	info->last_exit_status = exit_status;
}
