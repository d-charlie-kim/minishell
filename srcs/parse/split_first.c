/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_first.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 04:42:06 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/08 05:01:51 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

int	pipe_size_check(char *ptr)
{
	int i;
	int size;
	int	flag;

	i = 0;
	size = 0;
	flag = 0;
	while (ptr[i])
	{
		flag = check_quotes(ptr[i], flag);
		if (ptr[i] == '|' && flag == 0)
		{
			i++;
			return (size);
		}
		i++;
		size++;
	}
	return (size);
}

int	pipe_count(const char *str)
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
		if (flag == 0 && str[i] == '|')
			count++;
		i++;
	}
	return (count);
}

t_process	*first_split(const char *str, t_info *info)
{
	t_process	*processes;
	char		*ptr;
	char		*temp;
	char		*save;
	int			size;
	int			count;

	count = 0;
	info->process_count = pipe_count(str) + 1;
	processes = (t_process *)malloc(sizeof(t_process) * info->process_count);
	if (!processes)
		return (-1);
	save = str;
	while (count < info->process_count)
	{
		ptr = save;
		size = pipe_size_check(ptr); // 파이프 사이즈 체크 (한 프로세스의 사이즈)
		save += size + 1;                // 다음 파이프 체크할거 저장
// 여기서 포인터를 저장 안하고
// 밑에서 temp에 넣어줄때 ptr++ 해주고 싶은데 너무 꼬여버림

		size += env_size_check(ptr, size, info->env); // 한 프로세스 내의 환경변수 사이즈
		temp = (char *)malloc(sizeof(char) * (size + 1)); // 환경변수 치환한 총 길이로 할당
		temp[size] = '\0';                                // 끝 표시
		put_process_with_env(&temp, ptr, size, info->env); // 할당한 temp에 넣어주기 (여기서 환경변수 치환 작업도 들어가 있음)
		second_split(&processes[count], temp);            // 전부 채워진 temp를 token으로 나누기 위해 보냄
		free (temp);  // 다 사용한 temp 프리해줌
		count++;
	}
	return (processes);
}

// 1. 파이프 사이즈를 체크한다
// 2. 한 프로세스 안의 환경변수의 사이즈를 체크한다
// 3. 파이프 사이즈 + 환경변수 사이즈 로 메모리 할당을 한다.
// 4. 넣어준다. [temp]
// 5. temp에 들어간 친구 token count
// 6. temp token size check 해서 나누어 넣어주기 (bundle에)
// 7. temp free 해주기
// 8. bundle을 process 구조체에 분류해주기
// 9. 파싱이 끝나면 처음 str은 필요가 없나요
