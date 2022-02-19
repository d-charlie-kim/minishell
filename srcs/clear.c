/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:46:58 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/19 12:46:40 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

void	free_redirect(t_list *redirect)
{
	t_redirect_pair	*ptr;
	t_list			*temp;

	temp = redirect;
	while (temp)
	{
		ptr = (t_redirect_pair *)redirect->content;
		if (ptr->file_name)
		{
			free (ptr->file_name);
			ptr->file_name = NULL;
		}
		temp = temp->next;
	}
	ft_lstclear(&redirect, free);
}

void	free_envp(t_info *info)
{
	t_env	*temp;
	t_env	*next;

	temp = info->env;
	while (temp)
	{
		free (temp->key);
		free (temp->value);
		next = temp->next;
		free (temp);
		temp = next;
	}
}

void	free_process(t_process *process)
{
	t_process	*temp;

	temp = process;
	if (temp->instruction)
		free (temp->instruction);
	if (temp->option)
		ft_lstclear(&temp->option, free);
	if (temp->arguments)
		ft_lstclear(&temp->arguments, free);
	if (temp->redirect)
		free_redirect(temp->redirect);
	if (temp->heredoc_str)
		free (temp->heredoc_str);
}

void	free_all(t_info *info, t_process *processes, char *output)
{
	int			i;

	i = 0;
	free (output);
	while (i < info->process_count)
	{
		free_process(&processes[i]);
		i++;
	}
	free (processes);
}
