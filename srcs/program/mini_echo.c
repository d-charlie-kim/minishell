/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:34:32 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/11 16:55:27 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"

void	printing_echo(t_list *ptr)
{
	t_list	*temp;

	if (!ptr)
		return ;
	temp = ptr->content;
	while (!temp)
	{
		ft_putstr_fd((char *)temp->content, STDOUT_FILENO);
		temp = temp->next;
		if (!temp)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
}

int	mini_echo(t_info *info, t_process *process)
{
	int		flag;

	flag = 1;
	if (process->option && ((char *)process->option->content)[1] == 'n' \
			&& ((char *)process->option->content)[2] == '\0')
		printing_echo(process->option->next);
	else
	{
		printing_echo(process->option);
		flag = 0;
	}
	if (process->arguments)
	{
		ft_putchar_fd(' ', STDOUT_FILENO);
		printing_echo(process->arguments);
	}
	if (flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (exit_process(info, 0));
}
