/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:57:05 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/16 02:32:31 by jaejeong         ###   ########.fr       */
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
				ft_putstr_fd(strerror(ENOENT), STDERR_FILENO);
				exit(ENOENT);
			}
			close(fd);
		}
		redirect = redirect->next;
	}
}

static void	connect_last_file(t_list *redirect, int last)
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
}

static bool	heredoc_is_exist(t_list *redirect)
{
	t_redirect_pair	*pair;

	while (redirect)
	{
		pair = (t_redirect_pair *)(redirect->content);
		if (pair->symbol == DOUBLE_IN)
			return (true);
		redirect = redirect->next;
	}
	return (false);
}

static void	exec_heredoc(t_process *process, int last)
{
	pid_t	pid;

	pid = fork();
	if (pid )
}

void	set_input_redirect(t_process *process)
{
	int		last;
	t_list	*redirect;

	redirect = process->redirect;
	last = find_last_input_index(redirect);
	if (last == -1)
		return ;
	check_file_is_exist(redirect);
	connect_last_file(redirect, last);
	if (heredoc_is_exist(redirect))
		exec_heredoc(process, last);
}
