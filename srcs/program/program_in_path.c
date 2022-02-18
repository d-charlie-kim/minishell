/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_in_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 16:09:49 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/18 20:14:19 by dokkim           ###   ########.fr       */
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

static int	get_argv_size(t_list *option, t_list *arguments)
{
	int	argv_size;

	argv_size = 1 + ft_lstsize(option) + ft_lstsize(arguments);
	return (argv_size);
}

static void	add_option_in_argv(t_list *option, char ***argv)
{
	int	i;

	i = 1;
	while (option)
	{
		(*argv)[i] = (char *)(option->content);
		i++;
		option = option->next;
	}
}

static void	add_arguments_in_argv(t_list *arguments, char ***argv)
{
	int	i;

	i = 1;
	while ((*argv)[i])
		i++;
	while (arguments)
	{
		(*argv)[i] = (char *)(arguments->content);
		i++;
		arguments = arguments->next;
	}
}

static char	**setting_argv(t_process *process)
{
	int		argv_size;
	char	**argv;

	argv_size = get_argv_size(process->option, process->arguments);
	argv = (char **)malloc(sizeof(char *) * (argv_size + 1));
	if (!argv)
		print_error_and_exit("cannot allocate memory\n", ENOMEM);
	ft_bzero(argv, sizeof(char *) * (argv_size + 1));
	argv[0] = process->instruction;
	add_option_in_argv(process->option, &argv);
	add_arguments_in_argv(process->arguments, &argv);
	return (argv);
}

static int	get_envp_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

static void	add_value_in_envp(t_env *env, char **envp)
{
	int	i;
	int key_len;
	int value_len;

	i = 0;
	while (env)
	{
		key_len = ft_strlen(env->key);
		value_len = ft_strlen(env->value);
		envp[i] = (char *)malloc(sizeof(char) * (key_len + value_len + 2));
		if (!envp[i])
			print_error_and_exit("cannot allocate memory\n", ENOMEM);
		ft_strlcpy(&envp[i][0], env->key, key_len + 1);
		envp[i][key_len] = '=';
		ft_strlcpy(&envp[i][key_len + 1], env->value, value_len + 1);
		i++;
		env = env->next;
	}
}

static char	**setting_envp(t_env *env)
{
	int		envp_size;
	char	**envp;

	envp_size = get_envp_size(env);
	envp = (char **)malloc(sizeof(char *) * (envp_size + 1));
	if (!envp)
		print_error_and_exit("cannot allocate memory\n", ENOMEM);
	ft_bzero(envp, sizeof(char *) * (envp_size + 1));
	add_value_in_envp(env, envp);
	return (envp);
}

// void	free_envp(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		free(envp[i]);
// 		i++;
// 	}
// 	free(envp);
// }

void	find_instruction(t_info *info, t_process *process) // fork 이후 실행하도록.
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
