/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_process_to_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 04:42:08 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/14 15:24:49 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

static char	*get_str_token(const char *str)
{
	int		i;
	int		is_in_quotes;
	char	*ret;

	i = 0;
	is_in_quotes = 0;
	while ((str[i] != ' ' && str[i] != '<' && str[i] != '>' && str[i] != '\0')
			|| (is_in_quotes != NOT && str[i] != '\0'))
	{
		check_quotes(str[i], &is_in_quotes);
		i++;
	}
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (!ret)
		print_error_and_exit("cannot allocate memory\n", ENOMEM);
	ft_strlcpy(ret, str, i + 1);
	return (ret);
}

static char	*get_redirection_token(const char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[0] == str[i] && i < 2)
		i++;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (!ret)
		print_error_and_exit("cannot allocate memory\n", ENOMEM);
	ft_strlcpy(ret, str, i + 1);
	return (ret);
}

static char	*get_one_token(const char *str)
{
	if (str[0] == '<' || str[0] == '>')
		return (get_redirection_token(str));
	else
		return (get_str_token(str));
}

static int	classyfy_token(t_process *process, const char *token, int tag)
{
	int	i;

	if (token[0] == '<' || token[0] == '>')
	{
		if (tag == REDIRECTION)
			print_error_and_exit("syntax error near unexpected token\n", 0); // 올바른 에러코드 못찾음..
		else
			return (REDIRECTION);
	}
	if (tag == REDIRECTION)
		return (FILENAME);
	if (!process->instruction)
		return (INST);
	if (token[0] == '-')
	{
		i = 1;
		while (token[i] == '"' || token[i] == '\'')
			i++;
		if (('a' <= token[i] && token[i] <= 'z') || ('A' <= token[i] && token[i] <= 'Z'))
			return (OPTION);
	}
	return (ARG);
}

void	split_process_to_token(t_process *process, t_info *info, const char *str, int len)
{
	int		i;
	int		tag;
	char	*cur_token;
	char	*new_str;

	cur_token = NULL;
	new_str = replace_env_value(info, str, len);
	tag = 0;
	i = 0;
	while (new_str[i] == ' ')
		i++;
	while (new_str[i])
	{
		cur_token = get_one_token(&new_str[i]);
		i += ft_strlen(cur_token);
		tag = classyfy_token(process, cur_token, tag);
		remove_outside_quotes_in_str(&cur_token);
		save_token_in_struct(process, cur_token, tag);
		while (new_str[i] == ' ')
			i++;
	}
	free(new_str);
}
