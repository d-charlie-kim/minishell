/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_instruction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 16:09:49 by jaejeong          #+#    #+#             */
/*   Updated: 2021/12/20 18:36:51 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

void	find_inst_in_relative_path(t_process *process)
{
	
}

void	find_inst_in_absolute_path(t_process *process)
{
	
}

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
		ft_strlcpy(directory, &process[begin_index], end_index - begin_index + 1);
		instruction = find_inst_in_absolute_path();
		if (instruction)
			return (instruction);
		end_index++;
		begin_index = end_index;
	}
	return (NULL);
}

void	find_instruction(t_info *info, t_process *process)
{
	char	*instruction;
	char	*path;

	instruction = NULL;
	if (process->instruction[0] == '.')
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
