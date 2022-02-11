/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 01:09:52 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/11 21:31:41 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

static int	find_last_output_index(t_list *redirect)
{
	int				i;
	int				last;
	t_redirect_pair	*pair;

	i = 0;
	last = 0;
	while (redirect)
	{
		pair = (t_redirect_pair *)(redirect->content);
		if (pair->symbol == SINGLE_OUT || pair->symbol == DOUBLE_OUT)
			last = i;
		i++;
		redirect = redirect->next;
	}
	return (last);
}

static void	set_file(t_list *redirect)
{
	int				fd;
	t_redirect_pair	*pair;

	while (redirect)
	{
		pair = (t_redirect_pair *)(redirect->content);
		if (pair->symbol == DOUBLE_OUT)
		{
			fd = open(pair->file_name, O_CREAT);
			close(fd);
		}
		else if (pair->symbol == SINGLE_OUT)
		{
			fd = open(pair->file_name, O_CREAT | O_TRUNC);
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
	fd = open(pair->file_name, O_RDWR);
	close(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
}

void	set_output_redirect(t_process *process)
{
	int		last;
	t_list	*redirect;

	redirect = process->redirect;
	last = find_last_output_index(redirect);
	if (last == 0)
		return ;
	set_file(redirect);
	connect_last_file(redirect, last);
}
