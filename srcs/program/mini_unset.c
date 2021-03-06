/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:19:35 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/11 21:29:03 by dokkim           ###   ########.fr       */
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

	if (!info->env)
		return (exit_process(info, process, 0));
	if (process->option)
		return (err_option("unset", info, process));
	arguments = process->arguments;
	while (arguments != NULL)
	{
		target = (char *)arguments->content;
		if (env_is_valid(target))
			delete_env(&info->env, target);
		else
		{
			ft_putstr_fd("bash: unset: `", STDERR_FILENO);
			ft_putstr_fd(target, STDERR_FILENO);
			ft_putstr_fd("\': not a valid identifier\n", STDERR_FILENO);
		}
		arguments = arguments->next;
	}
	return (exit_process(info, process, 0));
}
