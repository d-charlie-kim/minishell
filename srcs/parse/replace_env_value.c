/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 04:46:22 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/20 18:46:11 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

static void	add_last_exit_status(char **str, int last_exit_status)
{
	int		i;
	char	*num_arr;

	num_arr = ft_itoa(last_exit_status);
	if (!num_arr)
		print_error_and_exit("cannot allocate memory\n", ENOMEM);
	i = 0;
	while (num_arr[i])
	{
		add_character_to_str(str, num_arr[i]);
		i++;
	}
	free(num_arr);
}

static char	*find_key_in_str(const char *str)
{
	int		i;
	char	*ret;

	i = 0;
	if (str[0] == '?')
	{
		ret = (char *)malloc(sizeof(char) * 2);
		ret[0] = '?';
		ret[1] = '\0';
		return (ret);
	}
	while (('A' <= str[i] && str[i] <= 'Z') || ('a' <= str[i] && str[i] <= 'z')
			|| ('0' <= str[i] && str[i] <= '9') || str[i] == '_')
		i++;
	if (i == 0)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * (i + 1));
	ft_strlcpy(ret, str, i + 1);
	return (ret);
}

static void	add_env_value(t_info *info, const char *key, char **str, int is_in_quotes)
{
	char	*value;

	if (!key)
	{
		add_character_to_str(str, '$');
		return ;
	}
	if (*key == '?')
	{
		add_last_exit_status(str, info->last_exit_status);
		return ;
	}
	value = get_env_value(info->env, key);
	if (!value)
		return ;
	if (is_in_quotes == NOT)
		add_character_to_str(str, '\"');
	while (*value)
	{
		add_character_to_str(str, *value);
		value++;
	}
	if (is_in_quotes == NOT)
		add_character_to_str(str, '\"');
}

char	*replace_env_value(t_info *info, const char *str, int len)
{
	int		i;
	int		is_in_quotes;
	char	*ret;
	char	*key;

	i = 0;
	is_in_quotes = NOT;
	ret = NULL;
	while (i < len)
	{
		check_quotes(str[i], &is_in_quotes);
		if (str[i] != '$' || is_in_quotes == SINGLE)
		{
			add_character_to_str(&ret, str[i]);
			i++;
		}
		else
		{
			if (str[i + 1] == '\'' || str[i + 1] == '\"')
			{
				i++;
				continue ;
			}
			key = find_key_in_str(&str[i + 1]);
			add_env_value(info, key, &ret, is_in_quotes);
			i += ft_strlen(key) + 1;
			free(key);
		}
	}
	return (ret);
}
