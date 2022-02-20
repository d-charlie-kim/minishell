/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 15:56:54 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/20 15:57:23 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

int	classify_token(t_process *process, const char *token, int tag)
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
