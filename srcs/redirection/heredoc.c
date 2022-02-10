/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 23:25:54 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/10 18:38:09 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

void	heredoc(t_info *info, t_process *process)
{
	t_list			*temp;
	t_redirect_pair	*here_doc;
	t_list			*arg_temp;
	char			*output;
	int				count;
	int				flag;

	flag = 0;
	count = 1;
	temp = process->redirect;
	while (temp != NULL) // heredoc 몇개인지 체크하는 함수 따로 뺄거
	{
		here_doc = (t_redirect_pair *)temp->content;
		if (here_doc->symbol == 2)
			count++;
		temp = temp->next;
	}


	if (!process->arguments) // 임시 빈 노드
	{
		flag = 1;
		process->arguments = (t_list *)malloc(sizeof(t_list));
		if (!process->arguments)
		{
			//error
		}
		process->arguments->content = NULL;
		process->arguments->next = NULL;
	}
	arg_temp = process->arguments;

	
	temp = process->redirect;
	while (count > 0 && temp != NULL)
	{
		here_doc = (t_redirect_pair *)temp->content;
		if (here_doc->symbol != 2)
		{
			temp = temp->next;
			continue ;
		}
		output = readline("> ");
		if (count == 1 && flag)
			printf("%s\n", output);
		if (strncmp(here_doc->file_name, output, ft_strlen(here_doc->file_name) + 1) == 0)
		{
			count--;
			temp = temp->next;
		}
	}
	if (flag)
	{
		arg_temp = process->arguments->next;
		free (process->arguments);
		process->arguments = arg_temp;
	}
	execute_program(info, process); //여기서 실행!!
}
