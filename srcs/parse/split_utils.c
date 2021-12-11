/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 04:44:06 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/11 22:15:46 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

int	check_quotes(char c, int in_quotes)
{
	if (in_quotes == NOT && c == '\'')
		in_quotes = SINGLE;
	else if (in_quotes == NOT && c == '"')
		in_quotes = DOUBLE;
	else if (in_quotes == SINGLE && c == '\'')
		in_quotes = NOT;
	else if (in_quotes == DOUBLE && c == '"')
		in_quotes = NOT;
	return (in_quotes);
}

char	*add_character_to_str(char *str, char character)
{
	int		str_size;
	char	*new_str;

	str_size = ft_strlen(str);
	new_str = (char *)malloc(sizeof(char) * (str_size + 2));
	if (!new_str)
		print_error_and_exit("cannot allocate memory\n", ENOMEM);
	if (str_size != 0)
	{
		ft_strlcpy(new_str, str, str_size + 1);
		free(str);
	}
	new_str[str_size] = character;
	new_str[str_size + 1] = '\0';
	return (new_str);
}

char	*remove_quotes_in_str(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			ret = add_character_to_str(ret, str[i]);
		i++;
	}
	free(str);
	return (ret);
}
