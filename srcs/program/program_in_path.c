/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_in_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 16:09:49 by jaejeong          #+#    #+#             */
/*   Updated: 2021/12/23 15:53:02 by jaejeong         ###   ########.fr       */
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

static void	execute_at_env_path(const char *path, t_process *process, char **argv)
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
		execve(inst, argv, NULL);
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
		printf("%s\n", (*argv)[i]);
		i++;
		arguments = arguments->next;
	}
}

static char	**setting_argv(t_process *process)
{
	int		argv_size;
	char	**argv;

	argv_size = get_argv_size(process->option, process->arguments);
	argv = (char **)malloc(sizeof(char *) * (argv_size + 1)); // free 해주기
	if (!argv)
		print_error_and_exit("cannot allocate memory\n", ENOMEM);
	ft_bzero(argv, sizeof(char *) * (argv_size + 1));
	argv[0] = process->instruction;
	add_option_in_argv(process->option, &argv);
	add_arguments_in_argv(process->arguments, &argv);
	argv[argv_size] = NULL;
	return (argv);
}

void	find_instruction(t_info *info, t_process *process) // fork 이후 실행하도록.
{
	char	*inst;
	char	*path;
	char	**argv;

	inst = process->instruction;
	argv = setting_argv(process);
	if (inst[0] == '.' || inst[0] == '/' || inst[0] == '~')
		execve(inst, argv, NULL);
	else
	{
		path = get_env_value(info->env, "PATH");
		execute_at_env_path(path, process, argv);
	}
}
