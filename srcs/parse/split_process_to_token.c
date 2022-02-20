/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_process_to_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 04:42:08 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/20 15:44:21 by jaejeong         ###   ########.fr       */
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
	while ((str[i] != ' ' && str[i] != '<' && str[i] != '>' && str[i] != '\0') \
		|| (is_in_quotes != NOT && str[i] != '\0'))
	{
		check_quotes(str[i], &is_in_quotes);
		i++;
	}
	if (is_in_quotes != NOT)
	{
		i = 1;
		while (str[i] != ' ' && str[i] != '\0')
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
		{
			parsing_error_print((char *)token);
			return (258);
		}
		else
			return (REDIRECTION);
	}
	if (tag == REDIRECTION)
		return (FILENAME);
	if (!process->instruction)
		return (INST);
	if (token[0] == '-' && !process->arguments)
	{
		i = 1;
		while (token[i] == '"' || token[i] == '\'')
			i++;
		if (ft_isalpha(token[i]))
			return (OPTION);
	}
	return (ARG);
}

 int	check_token(t_process *process, char **new_str, char **cur_token, int *tag)
 {
 	*tag = classyfy_token(process, *cur_token, *tag);
 	if (*tag == 258)
 	{
 		free (*cur_token);
 		free (*new_str);
 		return (258);
 	}
 	remove_outside_quotes_in_str(cur_token);
 	return (0);
 }

int	split_process_to_token(t_process *process, t_info *info, \
		const char *str, int len)
{
	int		i;
	int		tag;
	char	*cur_token;
	char	*new_str;

	cur_token = NULL;
	new_str = replace_env_value(info, str, len);
	tag = 0;
	i = input_delete_space(new_str);
	if (i == -1)
	{
		free(new_str);
		return (1);
	}
	while (new_str[i])
	{
		cur_token = get_one_token(&new_str[i]);
		i += ft_strlen(cur_token);
		if (check_token(process, &new_str, &cur_token, &tag))
			return (258);
		save_token_in_struct(process, cur_token, tag);
		while (new_str[i] == ' ')
			i++;
	}
	free(new_str);
	return (0);
}
