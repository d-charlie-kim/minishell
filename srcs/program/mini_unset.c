/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:19:35 by dokkim            #+#    #+#             */
/*   Updated: 2022/01/12 13:28:40 by dokkim           ###   ########.fr       */
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

void	mini_unset(t_info *info, t_process *process)
{
	t_list	*arguments;
	char	*target;
	
	if (!info->env)
		return ;
	arguments = process->arguments;
	while (arguments != NULL)
	{
		target = (char *)arguments->content;
		delete_env(&info->env, target);
		arguments = arguments->next;
	}
}