/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:40:55 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/05 16:30:05 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_split.h"
#include "../includes/mijeong.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	token_size_check(char *ptr)
{
	int count;
}

int	redir_count(char *ptr, int size)
{
	int i;
	int count;
	int	flag;

	i = 0;
	count = 1;
	flag = 0;
	while (i < size)
	{
		if (ptr[i] == '"' || ptr[i] == '\'')
		{
			if (flag == 0)
				flag = 1;
			else
				flag = 0;
		}
		if (flag == 0 && (ptr[i] == '>' || ptr[i] == '<'))
		{
			count++;
			while (ptr[i] == '>' || ptr[i] == '<')
				i++;
		}
		else if (flag == 0 && ptr[i] == ' ')
		{
			count++;
			while (ptr[i] == ' ')
				i++;
		}
		i++;
	}
	return (count);
}

void	second_split(t_process *bundle, char *ptr, int size)
{
	int	token_count;

	token_count = redir_count(ptr, size);
}

int	pipe_size_check(char *ptr)
{
	int size;
	int	flag;

	size = 0;
	flag = 0;
	while (*ptr)
	{
		if (*ptr && (*ptr == '"' || *ptr == '\'')) // "'|'" -> 파이프로 인식해버림
		{
			if (flag == 0)
				flag = 1;
			else
				flag = 0;
		}
		if (flag == 0 && *ptr == '|')
		{
			ptr++;
			return (size);
		}
		ptr++;
		size++;
	}
	return (size);
}

int	pipe_count(char *str)
{
	int i;
	int count;
	int	flag;

	i = 0;
	count = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] && (str[i] == '"' || str[i] == '\''))
		{
			if (flag == 0)
				flag = 1;
			else
				flag = 0;
		}
		if (flag == 0 && str[i] == '|')
			count++;
		i++;
	}
	return (count);
}

t_process	*first_split(char *str, t_info *info)
{
	t_process	*processes;
	char		*ptr;
	char		*temp;
	int			size;
	int			count;

	count = 0;
	info->process_count = pipe_count(str) + 1;
	ptr = str;
	processes = (t_process *)malloc(sizeof(t_process) * info->process_count);
	while (count < info->process_count)
	{
		temp = ptr;
		size = pipe_size_check(&ptr);
		second_split(&processes[count], temp, size);
		count++;
	}
	return (processes);
}

int main(void)
{
	char		*output;
	t_info		info;
	t_process	*processes;
	
	output = readline("test : ");
	processes = first_split(output, &info);
	processing_instruction(processes, info.process_count);
	free(output);
	return (0);
}
