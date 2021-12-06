/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:40:55 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/06 12:58:36 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "mini_split.h"

int	check_quotes(char c, int flag) // something wrong.....
{
	if (c == '"' && flag < 2)
		flag += 2;
	else if (c == '"')
		flag -= 2;
	else if (c == '\'' && flag != 1 && flag != 3)
		flag += 1;
	else if (c == '\'')
		flag -= 1;
	return (flag);
}

int	token_size_check(char *ptr) // char -> const char
{
	int i;
	int	flag;

	i = 0;
	flag = 0;
	while()
		;
}

int	token_count(char *ptr, int size) // char -> const char
{
	int i;
	int count;
	int	flag;

	i = 0;
	count = 1;
	flag = 0;
	while (i < size)
	{
		flag = check_quotes(ptr[i], flag);
		if (flag == 0 && (ptr[i] == ' ' || ptr[i] == '>' || ptr[i] == '<'))
		{
			count++;
			while (ptr[i] == ptr[i + 1])
				i++;
			if ((ptr[i] == '<' || ptr[i] == '>') && ptr[i + 1] == ' ')
				i++;
			else if (ptr[i] == ' ' && (ptr[i + 1] == '<' || ptr[i + 1] == '>'))
				i++;
			while (ptr[i] == ptr[i + 1])
				i++;
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
		str[i] = ptr[i];
		ptr++;
		i++;
	}
	str[i] = '\0';
}

void	second_split(t_process *process, char *ptr, int size)
{
	int	i;
	int	token_size;

	i = 0;
	token_size = 0;
	process->token_count = token_count(ptr, size) + 1;
	process->bundle = (char *)malloc(sizeof(char *) * (process->token_count));
	while (i < process->token_count)
	{
		token_size = token_size_check(ptr);
		process->bundle[i] = (char *)malloc(sizeof(char) * (token_size + 1));
		put_token(&(process->bundle[i]), ptr, token_size);
		i++;
	}
}

int	pipe_size_check(char *ptr)
{
	int size;
	int	flag;

	size = 0;
	flag = 0;
	while (*ptr)
	{
		// if (*ptr == '"' && flag < 2)
		// 	flag += 2;
		// else if (*ptr == '"')
		// 	flag -= 2;
		// else if (*ptr == '\'' && flag != 1 && flag != 3)
		// 	flag += 1;
		// else if (*ptr == '\'')
		// 	flag -= 1;
		flag = check_quotes(*ptr, flag);
		if (*ptr == '|' && flag == 0)
		{
			ptr++;
			return (size);
		}
		ptr++;
		size++;
	}
	return (size);
}

// int	pipe_count(char *str)   // Option2. 플래그 두개로 처리하기
// {
// 	int i;
// 	int count;
// 	int	flag1;
// 	int	flag2;

// 	i = 0;
// 	count = 0;
// 	flag1 = 0;
// 	flag2 = 0;
// 	while (str[i])
// 	{
// 		if (*str == '"' && flag1 == 0)
// 			flag1 = 1;
// 		else if (*str == '"' && flag1 == 1)
// 			flag1 = 0;
// 		else if (*str =='\'' && flag2 == 0)
// 			flag2 = 1;
// 		else if (*str =='\'' && flag2 == 1)
// 			flag2 = 0;
// 		else if (flag1 == 0 && flag2 == 0 && str[i] == '|')
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

int	pipe_count(char *str)	// char -> const char
							// Option1. 플래그 하나로 처리하기
{
	int i;
	int count;
	int	flag;

	i = 0;
	count = 0;
	flag = 0;
	while (str[i])
	{
		// if (str[i] == '"' && flag < 2)
		// 	flag += 2;
		// else if (str[i] == '"')
		// 	flag -= 2;
		// else if (str[i] == '\'' && flag != 1 && flag != 3)
		// 	flag += 1;
		// else if (str[i] == '\'')
		// 	flag -= 1;
		flag = check_quotes(str[i], flag);
		if (str[i] == '|' && flag == 0)
			count++;
		i++;
	}
	return (count);
}

t_process	*first_split(char *str, t_info *info) // char -> const char
{
	t_process	*processes;
	char		*ptr;
	char		*temp;
	int			size;
	int			count;

	count = 0;
	info->process_count = pipe_count(str) + 1;
	ptr = str;  // 있는 이유
	processes = (t_process *)malloc(sizeof(t_process) * info->process_count);
	while (count < info->process_count)
	{
		temp = ptr; // 있는 이유. temp의 값 변경 아직 안한 것인가?
		size = pipe_size_check(&ptr); // &ptr -> ptr?
		second_split(&processes[count], temp, size);
		count++;
	}
	return (processes);
}
