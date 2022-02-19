/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 12:30:34 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/19 12:37:47 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

static int	get_envp_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

static void	add_value_in_envp(t_env *env, char **envp)
{
	int	i;
	int	key_len;
	int	value_len;

	i = 0;
	while (env)
	{
		key_len = ft_strlen(env->key);
		value_len = ft_strlen(env->value);
		envp[i] = (char *)malloc(sizeof(char) * (key_len + value_len + 2));
		if (!envp[i])
			print_error_and_exit("cannot allocate memory\n", ENOMEM);
		ft_strlcpy(&envp[i][0], env->key, key_len + 1);
		envp[i][key_len] = '=';
		ft_strlcpy(&envp[i][key_len + 1], env->value, value_len + 1);
		i++;
		env = env->next;
	}
}

char	**setting_envp(t_env *env)
{
	int		envp_size;
	char	**envp;

	envp_size = get_envp_size(env);
	envp = (char **)malloc(sizeof(char *) * (envp_size + 1));
	if (!envp)
		print_error_and_exit("cannot allocate memory\n", ENOMEM);
	ft_bzero(envp, sizeof(char *) * (envp_size + 1));
	add_value_in_envp(env, envp);
	return (envp);
}
