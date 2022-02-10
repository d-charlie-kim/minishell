/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 00:39:52 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/10 20:30:48 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

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

void	print_error_and_exit(char *output, int error_num)
{
	write(STDERR_FILENO, output, ft_strlen(output));
	write(STDERR_FILENO, "\n", 1);
	exit(error_num);
}

int	exit_process(t_info *info, int exit_status)
{
	if (info->process_count == 1)
		return (exit_status);
	else
		exit(exit_status);
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