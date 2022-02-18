/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:46:58 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/18 21:14:37 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

void	free_redirect(t_list *redirect)
{
	t_redirect_pair *ptr;
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

void	free_all(t_info *info, t_process *processes, char *output)
{
	int			i;
	t_process	*temp;

	i = 0;
	free (output);
	while (i < info->process_count)
	{
		temp = &processes[i];
		if (temp->instruction)
			free (temp->instruction);
		if (temp->option)
			ft_lstclear(&temp->option, free);
		if (temp->arguments)
			ft_lstclear(&temp->arguments, free);
		if (temp->redirect)
			free_redirect(temp->redirect);
		i++;
	}
	free (processes);
}
