/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 19:06:37 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/10 16:15:04 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

static void	print_error(char *arg)
{
	char	*error_message;

	error_message = strerror(ENOENT);
	write(STDERR_FILENO, "bash: cd: ", 10);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, error_message, ft_strlen(error_message));
	write(STDERR_FILENO, "\n", 1);
}

int	mini_cd(t_info *info, t_process *process)
{
	int		ret;
	char	*arg;

	if (process->arguments)
		arg = (char *)(process->arguments->content);
	else
		arg = get_env_value(info->env, "HOME");
	ret = chdir(arg);
	if (ret == -1)
		print_error(arg);
	return (exit_process(info, ret));
}
