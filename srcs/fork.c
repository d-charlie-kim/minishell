/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 12:09:31 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/11 21:16:06 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

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
	{
		// set_input_redirect(process);
		execute_program(info, &processes[index]);
	}
	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		set_output_fd(pipe_fd);
		set_output_redirect(&processes[index - 1]);
		fork_recursive(info, processes, index - 1);
	}
	set_input_fd(pipe_fd);
	// set_input_redirect(process);
	waitpid(pid, NULL, 0);
	execute_program(info, &processes[index]);
}

void	fork_main(t_info *info, t_process *processes)
{
	int		exit_status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		set_output_redirect(&processes[info->process_count - 1]);
		fork_recursive(info, processes, info->process_count - 1);
	}
	waitpid(pid, &exit_status, 0);
	info->last_exit_status = exit_status;
}
