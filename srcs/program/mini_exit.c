/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:19:41 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/18 18:11:36 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

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

int	num_is_valid(char *arg)
{
	int		i;
	int		len;
	char	minus;

	i = 0;
	len = 0;
	while (arg[i] && arg[i] == ' ')
		i++;
	minus = '+';
	if (arg[i] == '+' || arg[i] == '-')
		minus = arg[i++];
	while (arg[i])
	{
		i++;
		len++;
	}
	if (len > 19)
		return (0);
	if ((ft_strncmp("9223372036854775808", arg + i - len, len) > 0) \
	|| ((ft_strncmp("9223372036854775808", arg + i - len, len) == 0) \
														&& minus == '-'))
		return (1);
	else
		return (0);
}

void	exit_error_print(t_info *info, int num, char *arg)
{
	if (num == 1)
	{
		print_exit(info, STDERR_FILENO);
		ft_putstr_fd("bash: exit: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	}
	else if (num == 2)
	{
		print_exit(info, STDERR_FILENO);
		ft_putstr_fd("bash: exit: too many arguments\n", STDERR_FILENO);
	}
}

int	mini_exit(t_info *info, t_process *process)
{
	unsigned char	exit_status;
	char			*arg;

	arg = get_arg(info, process);
	if (str_is_num(arg) && num_is_valid(arg))
		exit_status = ft_atoi(arg);
	else
	{
		exit_error_print(info, 1, arg);
		exit(1);
	}
	if (process->arguments->next)
	{
		exit_error_print(info, 2, arg);
		return (exit_process(info, 1));
	}
	else
	{
		print_exit(info, STDOUT_FILENO);
		exit(exit_status);
	}
	return (1);
}
