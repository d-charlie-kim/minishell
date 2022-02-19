/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 04:44:06 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/19 16:42:30 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

int	check_quotes(char c, int *is_in_quotes)
{
	if (*is_in_quotes == NOT && c == '\'')
	{
		*is_in_quotes = SINGLE;
		return (1);
	}
	else if (*is_in_quotes == NOT && c == '"')
	{
		*is_in_quotes = DOUBLE;
		return (1);
	}
	else if (*is_in_quotes == SINGLE && c == '\'')
	{
		*is_in_quotes = NOT;
		return (1);
	}
	else if (*is_in_quotes == DOUBLE && c == '"')
	{
		*is_in_quotes = NOT;
		return (1);
	}
	return (0);
}

void	add_character_to_str(char **str, char character)
{
	int		str_size;
	char	*new_str;

	str_size = ft_strlen(*str);
	new_str = (char *)malloc(sizeof(char) * (str_size + 2));
	if (!new_str)
		print_error_and_exit("cannot allocate memory\n", ENOMEM);
	if (*str)
	{
		ft_strlcpy(new_str, *str, str_size + 1);
		free(*str);
	}
	new_str[str_size] = character;
	new_str[str_size + 1] = '\0';
	*str = new_str;
}

void	remove_outside_quotes_in_str(char **str)
{
	int		i;
	int		is_in_quotes;
	char	*new_str;

	i = 0;
	is_in_quotes = NOT;
	new_str = NULL;
	while ((*str)[i])
	{
		if (check_quotes((*str)[i], &is_in_quotes))
		{
			i++;
			continue ;
		}
		add_character_to_str(&new_str, (*str)[i]);
		i++;
	}
	free(*str);
	*str = new_str;
}

int	input_delete_space(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (-1);
	else
		return (i);
}
