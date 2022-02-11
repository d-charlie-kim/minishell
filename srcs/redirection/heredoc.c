/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 23:25:54 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/11 21:22:27 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

int	check_heredoc_count(t_process *process)
{
	t_list			*redir_lst;
	t_redirect_pair	*redirect;
	int				count;

	count = 1;
	redir_lst = process->redirect;
	while (redir_lst != NULL)
	{
		redirect = (t_redirect_pair *)redir_lst->content;
		if (redirect->symbol == 2)
			count++;
		redir_lst = redir_lst->next;
	}
	return (count);
}

void	heredoc(t_process *process)
{
	t_list			*temp;
	t_redirect_pair	*redir_pair;
	char			*output;
	int				count;

	count = check_heredoc_count(process);
	temp = process->redirect;
	while (count > 0 && temp != NULL)
	{
		redir_pair = (t_redirect_pair *)temp->content;
		if (redir_pair->symbol != 2)
			temp = temp->next;
		else
		{
			output = readline("> ");
			if (count == 1)
				ft_putstr_fd(output, STDOUT_FILENO);
			if (!strncmp(redir_pair->file_name, output, \
							ft_strlen(redir_pair->file_name) + 1))
			{
				count--;
				temp = temp->next;
			}
		}
	}
}
