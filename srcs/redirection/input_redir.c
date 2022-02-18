/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:57:05 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/18 22:17:13 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

static int	find_last_input_index(t_list *redirect)
{
	int				i;
	int				last;
	t_redirect_pair	*pair;

	i = 0;
	last = -1;
	while (redirect)
	{
		pair = (t_redirect_pair *)(redirect->content);
		if (pair->symbol == SINGLE_IN || pair->symbol == DOUBLE_IN)
			last = i;
		i++;
		redirect = redirect->next;
	}
	return (last);
}

static void	check_file_is_exist(t_list *redirect)
{
	int				fd;
	t_redirect_pair	*pair;

	while (redirect)
	{
		pair = (t_redirect_pair *)(redirect->content);
		if (pair->symbol == SINGLE_IN)
		{
			fd = open(pair->file_name, 0);
			if (fd < 0)
			{
				ft_putstr_fd("bash: ", STDERR_FILENO);
				ft_putstr_fd(pair->file_name, STDERR_FILENO);
				ft_putstr_fd(": ", STDERR_FILENO);
				ft_putstr_fd(strerror(ENOENT), STDERR_FILENO);
				ft_putchar_fd('\n', STDERR_FILENO);
				exit(ENOENT);
			}
			close(fd);
		}
		redirect = redirect->next;
	}
}

static void	connect_heredoc(char *heredoc_str)
{
	pid_t	pid;
	int		pipe_fd[2];

	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		ft_putstr_fd(heredoc_str, pipe_fd[1]);
		close(pipe_fd[1]);
		exit(0);
	}
	else
	{
		close(pipe_fd[1]);
		close(STDIN_FILENO);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
}

static void	connect_last_file(t_list *redirect, char *heredoc_str, int last)
{
	int				fd;
	t_list			*node;
	t_redirect_pair	*pair;

	node = ft_lstfind_node(redirect, last);
	pair = (t_redirect_pair *)(node->content);
	if (pair->symbol == SINGLE_IN)
	{
		fd = open(pair->file_name, O_RDONLY);
		close(STDIN_FILENO);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (pair->symbol == DOUBLE_IN)
		connect_heredoc(heredoc_str);
}

void	set_input_redirect(t_process *process)
{
	int		last;
	char	*heredoc_str;
	t_list	*redirect;

	heredoc_str = process->heredoc_str;
	redirect = process->redirect;
	last = find_last_input_index(redirect);
	if (last == -1)
		return ;
	check_file_is_exist(redirect);
	connect_last_file(redirect, heredoc_str, last);
}
