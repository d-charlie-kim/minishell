/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 23:25:54 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/18 22:32:15 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

static void	save_str(char **save, char *output)
{
	char	*temp;

	add_character_to_str(save, '\n');
	temp = *save;
	*save = ft_strjoin(*save, output);
	free(temp);
}

static void	exec_heredoc(t_process *process, char *exit_str)
{
	char	*save;
	char	*output;

	if (process->heredoc_str)
		free(process->heredoc_str);
	save = (char *)malloc(sizeof(char) * 1);
	save[0] = '\0';
	while (1)
	{
		output = readline("> ");
		if (!ft_strncmp(output, exit_str, ft_strlen(output)))
		{
			free(output);
			break ;
		}
		save_str(&save, output);
		free(output);
	}
	add_character_to_str(&save, '\n');
	process->heredoc_str = save;
}

void	save_heredoc_str(t_info *info, t_process *processes)
{
	int 			i;
	char			*exit_str;
	t_list			*redirect;
	t_redirect_pair	*pair;

	i = 0;
	while (i < info->process_count)
	{
		redirect = (&processes[i])->redirect;
		while (redirect)
		{
			pair = (t_redirect_pair *)(redirect->content);
			if (pair->symbol == DOUBLE_IN)
			{
				exit_str = pair->file_name;
				exec_heredoc(&processes[i], exit_str);
			}
			redirect = redirect->next;
		}
		i++;
	}
}
