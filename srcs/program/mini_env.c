/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:32:02 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/11 16:49:19 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

static void	print_env(t_env *env)
{
	t_env	*temp;
	char	*address;

	temp = env;
	while (temp != NULL)
	{
		if (strncmp("_", temp->key, 2) == 0)
		{
			address = temp->value;
			temp = temp->next;
			continue ;
		}
		if (temp->value)
			printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
	printf("_=%s\n", address);
}

int	mini_env(t_info *info, t_process *process)
{
	char	*option;

	if (process->arguments)
	{
		write(STDERR_FILENO, "bash: env: too many arguments\n", 30);
		return (exit_process(info, 1));
	}
	else if (process->option)
	{
		option = (char *)(process->option->content);
		write(STDERR_FILENO, "env : illegal option -- ", 24);
		write(STDERR_FILENO, &(option[1]), 1);
		write(STDERR_FILENO, "\n", 1);
		return (exit_process(info, 1));
	}
	else
		print_env(info->env);
	return (exit_process(info, 0));
}
