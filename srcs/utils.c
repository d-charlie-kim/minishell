/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 00:39:52 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/10 00:15:17 by jaejeong         ###   ########.fr       */
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
