/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_in_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 16:09:49 by jaejeong          #+#    #+#             */
/*   Updated: 2021/12/22 17:24:31 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

char	*find_inst_in_env_path(const char *path, t_process *process)
{
	int		begin_index;
	int		end_index;
	char	*directory;
	char	*instruction;

	begin_index = 0;
	end_index = 0;
	while (begin_index < ft_strlen(path))
	{
		while (path[end_index] != ':' && path[end_index] != '\0')
			end_index++;
		directory = (char *)malloc(sizeof(char) * (end_index - begin_index + 1));
		if (!directory)
			print_error_and_exit("cannot allocate memory\n", ENOMEM);
		if (ft_strjoin(directory, process->instruction))
		ft_strlcpy(directory, &process[begin_index], end_index - begin_index + 1);
		instruction = find_inst_in_absolute_path();
		if (instruction)
			return (instruction);
		end_index++;
		begin_index = end_index;
	}
	return (NULL);
}

int	get_argv_size(t_list *option, t_list *arguments)
{
	int	argv_size;

	argv_size = 1 + ft_lstsize(option) + ft_lstsize(arguments);
	return (argv_size);
}

void	add_option_in_argv(t_list *option, char ***argv)
{
	int	i;

	i = 1;
	while (option)
	{
		*argv[i] = (char *)(option->content);
		i++;
		option = option->next;
	}
}

void	add_arguments_in_argv(t_list *arguments, char ***argv)
{
	int	i;

	i = 1;
	while (*argv[i])
		i++;
	while (arguments)
	{
		*argv[i] = (char *)(arguments->content);
		i++;
		arguments = arguments->next;
	}
}

char	**setting_argv(t_process *process)
{
	int		i;
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
		path = get_env_value;
		find_inst_in_env_path(path, process);
	}

	if (inst[0] == '.')
		instruction = find_inst_in_relative_path();
	else if (process->instruction[0] == '/' || process->instruction[0] == '~')
		instruction = find_inst_in_absolute_path();
	else
	{
		path = get_env_value(info->env, "PATH");
		instruction = find_inst_in_env_path(path, process);
	}
	if (instruction)
		execve(); // 명령어 실행시키기
}
