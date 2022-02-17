/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 12:09:31 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/17 12:30:00 by jaejeong         ###   ########.fr       */
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

void	set_output_fd(t_process *process, int pipe_fd[2],\
										int process_count, int i)
{
	if (i < process_count - 1)
	{
		close(pipe_fd[0]);
		close(STDOUT_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	set_output_redirect(process);
}

static void	create_processes(t_info *info, t_process *processes)
{
	int		i;
	int		input_fd;
	int		pipe_fd[2];

	i = 0;
	input_fd = 0;
	while (i < info->process_count)
	{
		if (i < info->process_count - 1)
			pipe(pipe_fd);
		(&processes[i])->pid = fork();
		if (processes[i].pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			set_input_fd(&processes[i], input_fd);
			set_output_fd(&processes[i], pipe_fd, info->process_count, i);
			execute_program(info, &processes[i]);
		}
		if (input_fd != 0)
			close(input_fd);
		close(pipe_fd[1]);
		input_fd = pipe_fd[0];
		i++;
	}
}

void	fork_main(t_info *info, t_process *processes)
{
	int		last_exit_status;
	int		first_exit_status;

	reset_output_mode(&(info->org_term));
	create_processes(info, processes);
	signal(SIGINT, SIG_IGN);
	waitpid(processes[0].pid, &first_exit_status, 0);
	sig_exit_handler(first_exit_status);
	waitpid(processes[info->process_count - 1].pid, &last_exit_status, 0);
	while (wait(NULL) > 0);
	info->last_exit_status = last_exit_status;
}
