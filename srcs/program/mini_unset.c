/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:19:35 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/10 20:27:42 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

void	delete_env(t_env **env, char *str)
{
	t_env	*temp;
	t_env	*target;
	int		len;

	temp = *env;
	len = ft_strlen(str);
	if (!ft_strncmp(temp->key, str, len + 1))
	{
		temp = temp->next;
		free (*env);
		*env = temp;
		return ;
	}
	while (temp->next != NULL)
	{
		if (!ft_strncmp(temp->next->key, str, len + 1))
		{
			target = temp->next;
			temp->next = target->next;
			free (target);
			return ;
		}
		temp = temp->next;
	}
}

int	mini_unset(t_info *info, t_process *process)
{
	t_list	*arguments;
	char	*target;
	char	*option;
	
	if (!info->env)
		return (exit_process(info, 0));
	if (process->option)
	{	
		option = (char *)(process->option->content);
		write(STDERR_FILENO, "bash: unset: -", 14);
		write(STDERR_FILENO, &(option[1]), 1);
		write(STDERR_FILENO, ": invalid option\n", 17);
		return (exit_process(info, 1));
	}
	arguments = process->arguments;
	while (arguments != NULL)
	{
		target = (char *)arguments->content;
		if (env_is_valid(target))
			delete_env(&info->env, target);
		else
		{
			write(STDERR_FILENO, "bash: unset: `", 14);
			write(STDERR_FILENO, &target, 1);
			write(STDERR_FILENO, "\': not a valid identifier\n", 26);
		}
		arguments = arguments->next;
	}
	return (exit_process(info, 0));
}
