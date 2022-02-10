/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:32:02 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/10 19:23:14 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

static void	print_env(t_env *env)
{
	t_env	*temp;
	char	*address;

	temp = env;
	while (temp != NULL)
	{
		if (strncmp("_", temp->key, 2) == 0)
		{
			address = temp->value;
			temp = temp->next;
			continue ;
		}
		if (temp->value)
			printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
	printf("_=%s\n", address);
}

int	mini_env(t_info *info, t_process *process)
{
	if (process->arguments)
	{
		write(STDERR_FILENO, "bash: env: too many arguments\n", 33);
		return (exit_process(info, 1));
	}
	else if (process->option)
	{
		
	}
	else
		print_env(info->env);
	return (exit_process(info, 0));

	/*
		arguments 가 있으면 error 출력
		env 단독으로 등장해야만 정상 출력
		export a 처럼 key 값은 주지만, value를 주지 않을 경우
		export 만 입력하면 정상 출력이 되고(key값만), env 만 입력하면 출력되지 않는다.
	*/
}
