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

int	str_is_num(char *arg)
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

void	print_exit(t_info *info, int fd)
{
	if (info->process_count == 1)
		ft_putstr_fd("exit\n", fd);
}

char	*get_arg(t_info *info, t_process *process)
{
	if (process->option)
		return ((char *)process->option->content);
	else if (process->arguments)
		return ((char *)(process->arguments->content));
	else
	{
		print_exit(info, STDOUT_FILENO);
		exit (0);
	}
}

int	mini_exit(t_info *info, t_process *process)
{
	int		exit_status;
	char	*arg;

	arg = get_arg(info, process);
	if (str_is_num(arg))
		exit_status = ft_atoi(arg);
	else
	{
		print_exit(info, STDERR_FILENO);
		ft_putstr_fd("bash: exit: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(1);
	}
	if (process->arguments->next)
	{
		print_exit(info, STDERR_FILENO);
		ft_putstr_fd("bash: exit: too many arguments\n", STDERR_FILENO);
	}
	else
	{
		print_exit(info, STDOUT_FILENO);
		exit(exit_status);
	}
	return (0);
}
