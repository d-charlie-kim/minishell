/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 12:09:31 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/19 14:24:09 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

void	set_input_fd(t_process *process, int input_fd)
{
	(void)process;
	if (input_fd != 0)
	{
		close(STDIN_FILENO);
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	set_input_redirect(process);
}

void	set_output_fd(t_process *process, int pipe_fd[2], bool is_last)
{
	if (!is_last)
	{
		close(pipe_fd[0]);
		close(STDOUT_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	set_output_redirect(process);
}

void	setting_child(t_process *process, \
							int input_fd, int pipe_fd[2], bool is_last)
{
	signal(SIGQUIT, SIG_DFL);
	set_input_fd(process, input_fd);
	set_output_fd(process, pipe_fd, is_last);
}

static void	create_processes(t_info *info, t_process *processes)
{
	int		i;
	int		input_fd;
	int		pipe_fd[2];

	i = -1;
	input_fd = 0;
	while (++i < info->process_count)
	{
		if (i < info->process_count - 1)
			pipe(pipe_fd);
		(&processes[i])->pid = fork();
		if (processes[i].pid == 0)
		{
			setting_child(&processes[i], \
					input_fd, pipe_fd, i == info->process_count - 1);
			execute_program(info, &processes[i]);
		}
		if (input_fd != 0)
			close(input_fd);
		if (i < info->process_count - 1)
		{
			close(pipe_fd[1]);
			input_fd = pipe_fd[0];
		}
	}
}

void	fork_main(t_info *info, t_process *processes)
{
	int		last_exit_status;
	int		first_exit_status;

	reset_output_mode(&(info->org_term));
	create_processes(info, processes);
	signal(SIGINT, SIG_IGN);
	waitpid(processes[info->process_count - 1].pid, &last_exit_status, 0);
	waitpid(processes[0].pid, &first_exit_status, 0);
	if (info->process_count == 1)
		sig_exit_handler(last_exit_status);
	else
		sig_exit_handler(first_exit_status);
	while (wait(NULL) > 0)
		;
	info->last_exit_status = last_exit_status / 256;
}
