/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:46:58 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/18 18:47:08 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

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
			ft_lstclear(&temp->redirect, free);    // redirect pair 안에 있는 filename도 free 해줘야 함
		i++;
	}
	free (processes);
}
