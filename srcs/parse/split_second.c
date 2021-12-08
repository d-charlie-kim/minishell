/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_second.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 04:42:08 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/08 14:29:47 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

int	token_size_check(char **ptr)
{
// 이 부분은 못하겠습니다.
// 전체적인 고민과 토의와 수정이 필요합니다.
	
	// int i;
	// int	flag;
	// int	size;

	// i = 0;
	// flag = 0;
	// size = 0;
	// while (*ptr == ' ')
	// 	*ptr++;
	// while (ptr[i])
	// {
	// 	flag = check_quotes(ptr[i], flag);
	// 	if (flag != 0)
	// 	{
	// 		size++;
	// 		i++;
	// 		continue ;
	// 	}
	// 	else if (ptr[i] == ' ')
	// 		i++;
		
	// }
	// while (ptr[i])
	// {
	// 	if (flag == 0 && ptr[i] == ' ')
	// 		i++;
	// }
}

int	token_count(const char *str)
{
	int i;
	int count;
	int	flag;

	i = 0;
	count = 0;
	flag = 0;
	while (str[i])
	{
		flag = check_quotes(str[i], flag);
		if (flag == 0 && (str[i] == '>' || str[i] == '<'))
		{
			i++;
			count++;
			while (str[i] && (str[i] == '<' || str[i] == '>'))
				i++;
			continue ;
		}
		else if (flag == 0 && (str[i] != ' '))
		{
			count++;
			while (str[i] && str[i] != '<' && str[i] != '>' && str[i] != ' ')
				i++;
			continue ;
		}
		i++;
	}
	return (count);
}

void	put_token(char *str, char *ptr, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		str[i] = *ptr;
		ptr++;
		i++;
	}
	str[i] = '\0';
}

void	classfy_init(t_process *process, char **bundle, int size)
{
	instruction_check(process, bundle, size);
	options_check(process, bundle, size);
	redirections_check(process, bundle, size);
	arguments_check(process, bundle, size);
}

void	second_split(t_process *process, char *str)
{
	int		i;
	int		token_size;
	int		sum;
	int		count;
	char	*ptr;

	i = 0;
	sum = 0;
	token_size = 0;
	count = token_count(str);
	process->bundle = (char *)malloc(sizeof(char *) * (count)); // char * -> char **
	if (!process->bundle)
		return (-1);
	ptr = str;
	while (i + 1 < count) // 토큰 갯수만큼이 아닌 한번 덜 도는 이유?
	{
		token_size = token_size_check(&ptr);
		sum += token_size;
		process->bundle[i] = (char *)malloc(sizeof(char) * (token_size + 1));
		put_token(&(process->bundle[i]), ptr, token_size);
		i++;
	}
	put_token(&(process->bundle[i]), ptr, ft_strlen(str) - sum);
	classfy_init(process, process->bundle, count);
}
