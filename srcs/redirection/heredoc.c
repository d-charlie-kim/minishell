/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 23:25:54 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/19 01:00:32 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

static void	save_str(char **save, char *output)
{
	char	*temp;

	if (ft_strlen(*save) > 0)
		add_character_to_str(save, '\n');
	temp = *save;
	*save = ft_strjoin(*save, output);
	free(temp);
}

static void	exec_heredoc(const char *exit_str, int output_fd)
{
	char	*save;
	char	*output;

	save = (char *)malloc(sizeof(char) * 1);
	save[0] = '\0';
	while (1)
	{
		output = readline("> ");
		if (!ft_strncmp(output, exit_str, ft_strlen(output)))
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
			process->heredoc_str = ft_strjoin(process->heredoc_str, save);
			if (temp)
				free(temp);
		}
		add_character_to_str(&(process->heredoc_str), '\n');
		free(save);
	}
}

static void	create_heredoc_process(t_info *info, t_process *process, const char *exit_str)
{
	pid_t	pid;
	int		exit_status;
	int		pipe_fd[2];

	if (process->heredoc_str)
		free(process->heredoc_str);
	reset_output_mode(&(info->org_term));
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
	sig_exit_handler(exit_status);
	read_heredoc_str(process, pipe_fd[0]);
	close(pipe_fd[0]);
	init_mom_setting(info);
}

void	save_heredoc_str(t_info *info, t_process *processes)
{
	int 			i;
	char			*exit_str;
	t_list			*redirect;
	t_redirect_pair	*pair;

	i = 0;
	while (i < info->process_count)
	{
		redirect = (&processes[i])->redirect;
		while (redirect)
		{
			pair = (t_redirect_pair *)(redirect->content);
			if (pair->symbol == DOUBLE_IN)
			{
				exit_str = pair->file_name;
				create_heredoc_process(info, &processes[i], exit_str);
			}
			redirect = redirect->next;
		}
		i++;
	}
}
