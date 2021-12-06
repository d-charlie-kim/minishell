/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:08:36 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/06 21:38:09 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

int	check_quotes(char c, int flag)
{
	if (flag == 0 && c == '"')
		flag = 1;
	else if (flag == 0 && c == '\'')
		flag = 2;
	else if (flag == 1 && c == '"')
		flag = 0;
	else if (flag == 2 && c == '\'')
		flag = 0;
	return (flag);
}

int	token_size_check(char *ptr)
{
	int i;
	int	flag;

	i = 0;
	flag = 0;
	if (flag == 0)
	{

	}
}

int	token_count(const char *ptr, int size)
{
	int i;
	int count;
	int	flag;

	i = 0;
	count = 0;
	flag = 0;
	while (i < size)
	{
		flag = check_quotes(ptr[i], flag);
		if (flag == 0 && (ptr[i] == '>' || ptr[i] == '<'))
		{
			i++;
			count++;
			while (i < size && (ptr[i] == '<' || ptr[i] == '>'))
				i++;
			continue ;
		}
		else if (flag == 0 && (ptr[i] != ' '))
		{
			count++;
			while (i < size && ptr[i] != '<' && ptr[i] != '>' && ptr[i] != ' ')
				i++;
			continue ;
		}
		i++;
	}
	return (count);
}

void	put_token(char *str, char *ptr, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		str[i] = *ptr;
		ptr++;
		i++;
	}
	str[i] = '\0';
}

void	classfy_init(t_process *process, char **bundle, int size)
{
	instruction_check(process, bundle, size);
	options_check(process, bundle, size);
	redirections_check(process, bundle, size);
	arguments_check(process, bundle, size);
}

void	second_split(t_process *process, char *ptr, int size)
{
	int	i;
	int	token_size;
	int	sum;
	int	count;

	i = 0;
	sum = 0;
	token_size = 0;
	count = token_count(ptr, size);
	process->bundle = (char *)malloc(sizeof(char *) * (count));
	while (i + 1 < count)
	{ 
		token_size = token_size_check(ptr);
		sum += token_size;
		process->bundle[i] = (char *)malloc(sizeof(char) * (token_size + 1));
		put_token(&(process->bundle[i]), ptr, token_size);
		i++;
	}
	put_token(&(process->bundle[i]), ptr, size - sum);
	ptr++;
	classfy_init(process, process->bundle, count);
}

int	pipe_size_check(char **ptr)
{
	int i;
	int size;
	int	flag;

	i = 0;
	size = 0;
	flag = 0;
	while (ptr[i])
	{
		flag = check_quotes(ptr[i], flag);
		if (ptr[i] == '|' && flag == 0)
		{
			i++;
			return (size);
		}
		i++;
		size++;
	}
	return (size);
}

int	pipe_count(const char *str)
{
	int i;
	int count;
	int	flag;

	i = 0;
	count = 0;
	flag = 0;
	while (str[i])
	{
		flag = check_quotes(str[i], flag);
		if (flag == 0 && str[i] == '|')
			count++;
		i++;
	}
	return (count);
}

t_process	*first_split(const char *str, t_info *info)
{
	t_process	*processes;
	char		*ptr;
	int			size;
	int			count;

	count = 0;
	info->process_count = pipe_count(str) + 1;
	ptr = str;
	processes = (t_process *)malloc(sizeof(t_process) * info->process_count);
	while (count < info->process_count)
	{
		size = pipe_size_check(ptr);
		second_split(&processes[count], ptr, size);
		count++;
	}
	return (processes);
}
