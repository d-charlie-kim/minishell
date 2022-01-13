/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:19:39 by dokkim            #+#    #+#             */
/*   Updated: 2022/01/12 14:12:24 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

t_env	*env_sorting(t_env *env)
{
	// 무슨 정렬을 사용할까
	// 버블 정렬밖에 떠오르지 않는다.
}

void	print_export(t_env *env)
{
	t_env	*sorted_env;
	t_env	*temp;
	int		i;

	sorted_env = env_sorting(env);
	temp = sorted_env;
	while (sorted_env!= NULL)
	{
		temp = sorted_env;
		printf("declare -x ");
		printf("%s=", sorted_env->key);
		printf("\"%s\"", sorted_env->value); // 만약에 value 값이 없을 경우 어떻게 출력되는지 확인
		//value 값이 비어 있어서 a=""  이렇게 출력되는 것과
		//value 값이 없어서 a 만 출력되는 것을 구분해줘야 한다.
		sorted_env = sorted_env->next;
		free (temp);
	}
				// temp 전체 free 해주는 부분 있어야 함

	// export용, env용 리스트를 따로 두지 않고, export 할때마다 정렬을 해주는 방향이 더 관리하기 편할 것 같다.
	// 시간적인 부분은 비효율적일 수 있으나
	// 환경변수가 엄청 많지 않기 때문에 괜찮.
}

int	mini_export(t_info *info, t_process *process)
{
	if (!process->arguments)
	{
		print_export(info->env);
	}
}

// 정렬을 먼저 해준 뒤에 (= 새로운 t_env 를 하나 만들어주고)
// declare -x 포함해서 출력을 한다.
// 아니면 정렬을 해주면서 
