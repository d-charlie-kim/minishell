/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:19:41 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/11 15:47:24 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

int	arg_is_num(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i] - '0'))
			i++;
		else
			return (0);
	}
	return (1);
}

int	mini_exit(t_info *info, t_process *process)
{
	int		exit_status;
	char	*arg;

	write(STDERR_FILENO, "exit\n", 5);
	if (!process->arguments && !process->option)
		exit(0);
	if (process->option)
		arg = (char *)(process->option->content);
	else
		arg = (char *)(process->arguments->content);
	if (arg_is_num(arg))
		exit_status = ft_atoi(arg);
	else
	{
		write(STDERR_FILENO, "bash: exit: ", 12);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": numeric argument required\n", 28);
		exit(1);
	}
	if (process->arguments->next)
	{
		write(STDERR_FILENO, "bash: exit: too many arguments\n", 31);
		return (exit_process(info, 1));
	}
	else
		exit(exit_status);
}
