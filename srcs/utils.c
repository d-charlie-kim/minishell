/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 00:39:52 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/19 17:17:37 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

void	save_str(char **save, char *output)
{
	char	*temp;

	if (ft_strlen(*save) > 0)
		add_character_to_str(save, '\n');
	temp = *save;
	*save = ft_strjoin(*save, output);
	free(temp);
}

char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (!(ft_strncmp(env->key, key, ft_strlen(key) + 1)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	exit_process(t_info *info, t_process *process, int exit_status)
{
	if (info->process_count == 1)
		return (exit_status);
	else
	{
		free_process(process);
		free_envp(info);
		exit(exit_status);
	}
}

int	env_is_valid(char *target)
{
	int	i;

	i = 1;
	if (target[0] != '_' && !ft_isalpha(target[0]))
		return (0);
	while (target[i])
	{
		if (ft_isalpha(target[i]) || ft_isdigit(target[i]) || target[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

int	str_is_num(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] == ' ')
		i++;
	if (arg[i] && (arg[i] == '+' || arg[i] == '-'))
		i++;
	if (arg[i] == '\0')
		return (0);
	while (arg[i])
	{
		if (ft_isdigit(arg[i]))
			i++;
		else
			return (0);
	}
	return (1);
}
