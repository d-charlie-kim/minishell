/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 04:46:22 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/10 01:25:11 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

char	*find_key_in_str(const char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (('A' <= str[i] && str[i] <= 'Z') || ('a' <= str[i] && str[i] <= 'z')
			|| '0' <= str[i] && str[i] <= '9' || str[i] == '_')
		i++;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	strlcpy(ret, str, i + 1);
	return (ret);
}

void	add_env_value(t_env *env, char *key, char *str)
{
	char	*value;

	value = get_env_value(env, key);
	while (*value)
	{
		str = add_character_to_str(str, *value);
		value++;
	}
}

char	*replace_env_value(t_info *info, const char *str, int len)
{
	int		i;
	int		in_quotes;
	char	*ret;
	char	*key;

	i = 0;
	in_quotes = 0;
	ret = NULL;
	while (i < len)
	{
		in_quotes = check_quotes(in_quotes);
		if (str[i] != '$' || in_quotes != NOT)
		{
			ret = add_character_to_str(ret, str[i]);
			i++;
		}
		else
		{
			key = find_key_in_str(&str[i]);
			add_env_value(info->env, key, ret);
			i += ft_strlen(key) + 1;
			free(key);
		}
	}
	return (ret);
}
