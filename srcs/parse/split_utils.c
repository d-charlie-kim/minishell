/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 04:44:06 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/10 01:55:11 by jaejeong         ###   ########.fr       */
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
	ft_strlcpy(new_str, str, str_size + 1);
	new_str[str_size] = character;
	new_str[str_size + 1] = '\0';
	free(str);
	return (new_str);
}
