/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_classify.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:26:17 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/06 21:38:44 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	instruction_check(t_process *process, char **bundle, int size)
{
	int	i;

	i = 0;
	process->instruction = NULL;
	while (i < size)
	{
		if (bundle[i][0] == '<' || bundle[i][0] == '>')
		{
			i += 2;
			continue ;
		}
		else
		{
			process->instruction = bundle[i];
			break ;
		}
	}
}

void	options_check(t_process *process, char **bundle, int size)
{

}

void	redirections_check(t_process *process, char **bundle, int size)
{

}

void	arguments_check(t_process *process, char **bundle, int size)
{

}