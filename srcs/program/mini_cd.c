/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 19:06:37 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/14 16:42:11 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

static void	print_error(char *arg)
{
	char	*error_message;

	error_message = strerror(ENOENT);
	ft_putstr_fd("bash: cd: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error_message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	update_pwd(t_env *env)
{
	char	buf[PATH_MAX];
	t_env	*temp;
	char	*old_pwd;
	char	*new_pwd;

	getcwd(buf, PATH_MAX);
	new_pwd = ft_strdup(buf);
	temp = is_already_exist("PWD", env);
	if (temp)
	{
		old_pwd = temp->value;
		temp->value = new_pwd;
	}
	temp = is_already_exist("OLDPWD", env);
	if (temp)
	{
		free (temp->value);
		temp->value = old_pwd;
	}
}

int	mini_cd(t_info *info, t_process *process)
{
	int		ret;
	char	*arg;

	if (process->option)
		return (err_option("cd", info, process));
	if (process->arguments)
		arg = (char *)(process->arguments->content);
	else
		arg = get_env_value(info->env, "HOME");
	ret = chdir(arg);
	if (ret == -1)
	{
		print_error(arg);
		ret = 1;
	}
	update_pwd(info->env);
	return (exit_process(info, ret));
}
