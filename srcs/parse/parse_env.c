/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 16:14:33 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/20 15:13:20 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

static void	add_new_node(t_env **env, t_env *new_node)
{
	t_env	*last_node;

	if (!*env)
	{
		*env = new_node;
		return ;
	}
	last_node = *env;
	while (last_node->next)
		last_node = last_node->next;
	last_node->next = new_node;
}

static void	save_key_and_value(t_env **env, const char *data)
{
	int		begin;
	int		size;
	char	*key;
	char	*value;
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		print_error_and_exit("cannot allocate memory\n", ENOMEM);
	begin = 0;
	size = 0;
	while (data[size] != '=')
		size++;
	key = (char *)malloc(sizeof(char) * (size + 1));
	if (!key)
		print_error_and_exit("cannot allocate memory\n", ENOMEM);
	ft_strlcpy(key, &data[begin], size + 1);
	begin = size + 1;
	size = 0;
	while (data[begin + size] != '\0')
		size++;
	value = (char *)malloc(sizeof(char) * (size + 1));
	if (!value)
		print_error_and_exit("cannot allocate memory\n", ENOMEM);
	ft_strlcpy(value, &data[begin], size + 1);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	add_new_node(env, new_node);
}

void	parse_envp(t_info *info, char **envp)
{
	int	i;

	i = 0;
	info->env = NULL;
	while (envp[i])
	{
		save_key_and_value(&(info->env), envp[i]);
		i++;
	}
}
