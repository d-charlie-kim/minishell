/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:34:32 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/18 18:20:16 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"

int	printing_echo(t_list *ptr, int ret)
{
	t_list	*temp;

	if (!ptr)
		return (ret);
	temp = ptr;
	while (temp)
	{
		ft_putstr_fd((char *)temp->content, STDOUT_FILENO);
		temp = temp->next;
		if (temp)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	return (ret);
}

int	echo_option_check(char *option)
{
	int	i;

	i = 1;
	while (option[i] == 'n')
		i++;
	if (option[i] == '\0')
		return (1);
	else
		return (0);
}

int	echo_option_print(t_process *process)
{
	t_list	*temp;
	char	*option;
	int		ret;

	ret = 1;
	temp = process->option;
	while (temp)
	{
		option = (char *)temp->content;
		if (echo_option_check(option))
		{
			ret = 0;
			temp = temp->next;
			continue ;
		}
		else
			return (printing_echo(temp, ret));
	}
	return (ret);
}

void	echo_arg_print(t_process *process, int flag)
{
	if (process->arguments)
	{
		if (process->option && flag)
			ft_putchar_fd(' ', STDOUT_FILENO);
		printing_echo(process->arguments, 0);
	}
}

int	mini_echo(t_info *info, t_process *process)
{
	int		flag;

	flag = echo_option_print(process);
	echo_arg_print(process, flag);
	if (flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (exit_process(info, process, 0));
}
