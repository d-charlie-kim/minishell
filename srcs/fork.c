/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 12:09:31 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/17 10:34:52 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

//static void	set_output_fd(int pipe_fd[])
//{
//	close(pipe_fd[0]);
//	close(STDOUT_FILENO);
//	dup2(pipe_fd[1], STDOUT_FILENO);
//	close(pipe_fd[1]);
//}

//static void	set_input_fd(int pipe_fd[])
//{
//	close(pipe_fd[1]);
//	close(STDIN_FILENO);
//	dup2(pipe_fd[0], STDIN_FILENO);
//	close(pipe_fd[0]);
//}

//static void	fork_recursive(t_info *info, t_process *processes, int index)
//{
//	pid_t	pid;
//	int		pipe_fd[2];

//	if (index == 0)
//	{
//		// set_input_redirect(process);
//		execute_program(info, &processes[index]);
//	}
//	pipe(pipe_fd);
//	pid = fork();
//	if (pid == 0)
//	{
//		set_output_fd(pipe_fd);
//		set_output_redirect(&processes[index - 1]);
//		fork_recursive(info, processes, index - 1);
//	}
//	set_input_fd(pipe_fd);
//	// set_input_redirect(process);
//	execute_program(info, &processes[index]);
//}

//void	fork_main(t_info *info, t_process *processes)
//{
//	int		exit_status;
//	pid_t	pid;

//	pid = fork();
//	if (pid == 0)
//	{
//		reset_output_mode(&(info->org_term));
//		//set_output_redirect(&processes[info->process_count - 1]);
//		fork_recursive(info, processes, 1);
//	}
//	init_child_setting(info);
//	waitpid(pid, &exit_status, 0);
//	info->last_exit_status = exit_status;
//}

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

static pid_t	create_processes(t_info *info, t_process *processes)
{
	pid_t	pid;
	int		i;
	int		input_fd;
	int		pipe_fd[2];

	i = 0;
	input_fd = 0;
	while (i < info->process_count)
	{
		if (i < info->process_count - 1)
			pipe(pipe_fd);
		pid = fork();
		if (i == 0)
			info->first_process_pid = pid;
		if (pid == 0)
		{
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
	return (pid);
}

void	fork_main(t_info *info, t_process *processes)
{
	int		exit_status;
	int		first_process_exit_status;
	pid_t	pid;

	reset_output_mode(&(info->org_term));
	pid = create_processes(info, processes);
	init_child_setting(info);
	waitpid(info->first_process_pid, &first_process_exit_status, 0);
	if (first_process_exit_status == 2)
		ft_putstr_fd("\n", STDOUT_FILENO);
	else if (first_process_exit_status == 3)
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
	waitpid(pid, &exit_status, 0);
	while (wait(NULL) > 0);
	info->last_exit_status = exit_status;
}
