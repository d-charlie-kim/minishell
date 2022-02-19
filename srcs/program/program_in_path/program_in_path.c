/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_in_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 16:09:49 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/19 12:37:05 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

static char	*get_inst_with_path_route(const char *path,
		const char *inst, int begin, int end)
{
	char	*route;
	char	*ret;

	route = (char *)malloc(sizeof(char) * (end - begin + 2));
	if (!route)
		print_error_and_exit("cannot allocate memory\n", ENOMEM);
	ft_strlcpy(route, &path[begin], end - begin + 1);
	route[end - begin] = '/';
	route[end - begin + 1] = '\0';
	ret = ft_strjoin(route, inst);
	free(route);
	if (!ret)
		print_error_and_exit("cannot allocate memory\n", ENOMEM);
	return (ret);
}

static void	execute_at_env_path(const char *path, \
						t_process *process, char **argv, char **envp)
{
	int		begin;
	int		end;
	char	*inst;

	begin = 0;
	end = 0;
	while (begin < (int)ft_strlen(path))
	{
		while (path[end] != ':' && path[end] != '\0')
			end++;
		inst = get_inst_with_path_route(path, process->instruction,
				begin, end);
		execve(inst, argv, envp);
		end++;
		begin = end;
	}
}

void	find_instruction(t_info *info, t_process *process)
{
	char	*inst;
	char	*path;
	char	**argv;
	char	**envp;

	inst = process->instruction;
	argv = setting_argv(process);
	envp = setting_envp(info->env);
	if (process->instruction[0] == '.' || process->instruction[0] == '/')
		execve(inst, argv, envp);
	else if (get_env_value(info->env, "PATH"))
	{
		path = get_env_value(info->env, "PATH");
		execute_at_env_path(path, process, argv, envp);
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(process->instruction, STDERR_FILENO);
		print_error_and_exit(": command not found", 127);
	}
	else
		execve(inst, argv, envp);
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(process->instruction, STDERR_FILENO);
	print_error_and_exit(": No such file or directory", 127);
}
