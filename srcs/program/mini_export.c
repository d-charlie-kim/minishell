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
#include "libft.h"

void	put_new_node_to_sorted_env(t_env *sorted_env, t_env *new_node)
{
	t_env	*front_node;
	t_env	*second_node;

	second_node = sorted_env;
	front_node = second_node->next;
	while (front_node != NULL)
	{
		if (ft_strncmp(front_node->key, new_node->key, ft_strlen(front_node->key) + 1) > 0)
		{
			second_node->next = new_node;
			new_node->next = front_node;
			return ;
		}
		second_node = front_node;
		front_node = front_node->next;
	}
	if (front_node == NULL)
		second_node->next = new_node;
}

t_env	*make_sorted_env(t_env *env)
{
	t_env	*ret;
	t_env	*temp;
	t_env	*new_node;
	t_env	*sorted_env;

	temp = env;
	sorted_env = (t_env *)malloc(sizeof(t_env));
	if (!sorted_env)
	{
		//error 처리
	}
	sorted_env->next = NULL;
	while (temp != NULL)
	{
		new_node = (t_env *)malloc(sizeof(t_env));
		if (!new_node)
		{
			//error  처리
		}
		new_node->key = temp->key;
		new_node->value = temp->value;
		new_node->next = NULL;
		if (sorted_env->next == NULL)
			sorted_env->next = new_node;
		else
			put_new_node_to_sorted_env(sorted_env, new_node);
		temp = temp->next;
	}
	ret = sorted_env->next;
	free (sorted_env);
	return (ret);
}

void	print_export(t_env *env)
{
	t_env	*sorted_env;
	t_env	*temp;

	sorted_env = make_sorted_env(env);
	while (sorted_env!= NULL)
	{
		temp = sorted_env;
		printf("declare -x ");
		if (sorted_env->value != NULL)
		{
			printf("%s=", sorted_env->key);
			printf("\"%s\"\n", sorted_env->value);
		}
		/*
			만약에 value 값이 없을 경우 어떻게 출력되는지 확인
			value 값이 비어 있어서 a=""  이렇게 출력되는 것과
			value 값이 없어서 a 만 출력되는 것을 구분해줘야 한다.
		*/
		sorted_env = sorted_env->next;
		free (temp);
	}
	free (sorted_env);
	/*
		export용, env용 리스트를 따로 두지 않고, export 할때마다 정렬을 해주는 방향이 더 관리하기 편할 것 같다.
		시간적인 부분은 비효율적일 수 있으나
		환경변수가 엄청 많지 않기 때문에 괜찮.
	*/
}

// void	put_env(t_env *env, t_list *arguments)
// {

// }

int	mini_export(t_info *info, t_process *process)
{
	if (!process->arguments)
		print_export(info->env);
	// else
	// 	put_env(info->env, process->arguments);
	return (0);
}
