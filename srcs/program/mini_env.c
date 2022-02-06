/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:32:02 by jaejeong          #+#    #+#             */
/*   Updated: 2022/01/12 13:57:39 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

void	print_env(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (temp->value)
			printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
	//printf("_=/ pwd (현재 디렉토리)/./minishell");
}

void	mini_env(t_info *info, t_process *process)
{
	if (process->arguments)
	{
		printf("env: %s: No such file or directory", (char *)process->arguments->content);
		return ;
	}
	else
		print_env(info->env);
	// arguments 가 있으면 error 출력
	// env 단독으로 등장해야만 정상 출력

	// export a 처럼 key 값은 주지만, value를 주지 않을 경우
	// export 만 입력하면 정상 출력이 되고(key값만), env 만 입력하면 출력되지 않는다.
}
