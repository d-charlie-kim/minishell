/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line_to_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 04:42:06 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/20 15:17:49 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

void	parsing_error_print(char *str)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

static int	num_of_character_in_pipe(const char *ptr)
{
	int	size;
	int	is_in_quotes;

	size = 0;
	is_in_quotes = 0;
	while (ptr[size])
	{
		check_quotes(ptr[size], &is_in_quotes);
		if (ptr[size] == '|' && is_in_quotes == NOT)
			return (size);
		size++;
	}
	return (size);
}

static int	get_pipe_count(const char *str)
{
	int	i;
	int	pipe_count;
	int	is_in_quotes;

	i = 0;
	pipe_count = 0;
	is_in_quotes = 0;
	while (str[i])
	{
		check_quotes(str[i], &is_in_quotes);
		if (str[i] == '|' && is_in_quotes == NOT)
			pipe_count++;
		i++;
	}
	if (is_in_quotes != NOT)
	{
		parsing_error_print("newline");
		return (-2);
	}
	return (pipe_count);
}

t_process	*split_error(int ret, t_info *info)
{
	if (ret != 258 && info->process_count != 1)
		parsing_error_print("|");
	return (NULL);
}

t_process	*split_line_to_process(const char *str, t_info *info)
{
	int			i;
	int			len;
	int			ret;
	t_process	*processes;

	info->process_count = get_pipe_count(str) + 1;
	if (info->process_count == -1)
		return (NULL);
	processes = (t_process *)malloc(sizeof(t_process) * info->process_count);
	if (!processes)
		print_error_and_exit("cannot allocate memory\n", ENOMEM);
	ft_bzero(processes, sizeof(t_process) * info->process_count);
	i = 0;
	while (i < info->process_count)
	{
		len = num_of_character_in_pipe(str);
		ret = split_process_to_token(&processes[i], info, str, len);
		if (ret)
			return (split_error(ret, info));
		str += len + 1;
		i++;
	}
	return (processes);
}
