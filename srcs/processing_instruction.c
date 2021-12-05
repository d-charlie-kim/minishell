/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_instruction.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 12:09:31 by jaejeong          #+#    #+#             */
/*   Updated: 2021/12/05 17:24:47 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"

void	make_pipe_and_fork(t_process *processes, t_process *cur_process,
			int child_index, bool *can_enter)
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
		*can_enter = false;
	}
	else
	{
		close(STDOUT_FILENO);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		cur_process = &processes[child_index];
	}
}

void	processing_instruction(t_process *processes, int process_count)
{
	int			child_index;
	int			exit_status;
	bool		can_enter;
	t_process	*cur_process;

	child_index = process_count - 1;
	cur_process = NULL;
	can_enter = true;
	while (child_index >= 0)
	{
		if (can_enter)
			make_pipe_and_fork(processes, cur_process, child_index, &can_enter);
		child_index--;
	}
	if (cur_process)
	{
		exit_status = any_program(cur_process);
		exit(exit_status);
	}
}
