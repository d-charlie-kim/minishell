/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line_to_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 04:42:06 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/20 17:00:06 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

static int	num_of_character_in_pipe(const char *ptr)
{
	int size;
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
	int i;
	int pipe_count;
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
	return (pipe_count);
}

t_process	*split_line_to_process(const char *str, t_info *info)
{
	int			i;
	int			len;
	t_process	*processes;

	info->process_count = get_pipe_count(str) + 1;
	processes = (t_process *)malloc(sizeof(t_process) * info->process_count);
	if (!processes)
		print_error_and_exit("cannot allocate memory\n", ENOMEM);
	ft_bzero(processes, sizeof(t_process) * info->process_count);
	i = 0;
	while (i < info->process_count)
	{
		len = num_of_character_in_pipe(str);
		split_process_to_token(&processes[i], info, str, len);
		str += len + 1;
		i++;
	}
	return (processes);
}
