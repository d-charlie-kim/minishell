/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:40:55 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/03 22:43:57 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	pipe_check(char *str)
{
	int i;
	int count;
	int	flag;

	i = 0;
	count = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] && (str[i] == '"' || str[i] == '\''))
		{
			if (flag == 0)
				flag = 1;
			else
				flag = 0;
		}
		if (flag == 0 && str[i] == '|')
			count++;
		i++;
	}
	return (count);
}

void	ft_split(char *str)
{
	int	pipe_count;

	pipe_count = pipe_check(str);
	printf("how many pipe : %d\n", pipe_count);
}

int main(void)
{
	char *output;
	
	output = readline("test : ");
	ft_split(output);
	free(output);
	return (0);
}
