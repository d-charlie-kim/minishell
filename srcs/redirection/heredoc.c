/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 23:25:54 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/20 15:13:36 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

static void	exec_heredoc(const char *exit_str, int output_fd)
{
	char	*save;
	char	*output;

	save = (char *)malloc(sizeof(char) * 1);
	if (!save)
		print_error_and_exit("cannot allocate memory\n", ENOMEM);
	save[0] = '\0';
	while (1)
	{
		output = readline("> ");
		if (!output || !ft_strncmp(output, exit_str, ft_strlen(output)))
		{
			free(output);
			break ;
		}
		save_str(&save, output);
		free(output);
	}
	add_character_to_str(&save, '\n');
	ft_putstr_fd(save, output_fd);
	free(save);
	exit(0);
}

static void	read_heredoc_str(t_process *process, int input_fd)
{
	char	*save;
	char	*temp;

	while (get_next_line(input_fd, &save) > 0)
	{
		if (!(process->heredoc_str))
			process->heredoc_str = ft_strdup(save);
		else
		{
			temp = process->heredoc_str;
			process->heredoc_str = ft_strjoin(temp, save);
			if (temp)
				free(temp);
		}
		add_character_to_str(&(process->heredoc_str), '\n');
		free(save);
	}
	free (save);
}

static int	create_heredoc_process(t_info *info, t_process *process, \
												const char *exit_str)
{
	pid_t	pid;
	int		exit_status;
	int		pipe_fd[2];

	if (process->heredoc_str)
	{
		free(process->heredoc_str);
		process->heredoc_str = NULL;
	}
	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(pipe_fd[0]);
		exec_heredoc(exit_str, pipe_fd[1]);
	}
	signal(SIGINT, SIG_IGN);
	close(pipe_fd[1]);
	waitpid(pid, &exit_status, 0);
	read_heredoc_str(process, pipe_fd[0]);
	close(pipe_fd[0]);
	init_mom_setting(info);
	return (exit_status);
}

int	save_heredoc_str(t_info *info, t_process *process)
{
	int				exit_status;
	char			*exit_str;
	t_list			*redirect;
	t_redirect_pair	*pair;

	redirect = process->redirect;
	while (redirect)
	{
		pair = (t_redirect_pair *)(redirect->content);
		if (pair->symbol == DOUBLE_IN)
		{
			exit_str = pair->file_name;
			exit_status = create_heredoc_process \
						(info, process, exit_str);
			if (exit_status != 0)
			{
				sig_exit_handler(exit_status);
				return (1);
			}
		}
		redirect = redirect->next;
	}
	return (0);
}

int	heredoc_handler(t_info *info, t_process *processes)
{
	int	i;

	i = 0;
	while (i < info->process_count)
	{
		if (save_heredoc_str(info, &processes[i]))
			return (1);
		i++;
	}
	return (0);
}
