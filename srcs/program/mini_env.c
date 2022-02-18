/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:32:02 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/11 21:31:10 by jaejeong         ###   ########.fr       */
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
		ft_putstr_fd("bash: env: too many arguments\n", STDERR_FILENO);
		return (exit_process(info, process, 1));
	}
	else if (process->option)
	{
		option = (char *)(process->option->content);
		ft_putstr_fd("env : illegal option -- ", STDERR_FILENO);
		ft_putstr_fd(&(option[1]), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (exit_process(info, process, 1));
	}
	else
		print_env(info->env);
	return (exit_process(info, process, 0));
}
