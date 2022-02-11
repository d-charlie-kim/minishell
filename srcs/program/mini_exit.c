/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:19:41 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/11 21:31:41 by dokkim           ###   ########.fr       */
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

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!process->arguments && !process->option)
		exit(0);
	if (process->option)
		arg = (char *)(process->option->content);
	else
		arg = (char *)(process->arguments->content);
	if (!arg_is_num(arg))
		exit_status = ft_atoi(arg);
	else
	{
		ft_putstr_fd("bash: exit: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(1);
	}
	if (process->arguments->next)
		ft_putstr_fd("bash: exit: too many arguments\n", STDERR_FILENO);
	else
		exit(exit_status);
	return (0);
	info = NULL;
}
