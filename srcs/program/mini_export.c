/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:19:39 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/10 00:13:54 by jaejeong         ###   ########.fr       */
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
		else
			printf("%s\n", sorted_env->key);
		/*
			만약에 value 값이 없을 경우 어떻게 출력되는지 확인
			value 값이 비어 있어서 a=""  이렇게 출력되는 것과
			value 값이 없어서 a 만 출력되는 것을 구분해줘야 한다.
		*/
		sorted_env = sorted_env->next;
		free (temp);
	}
	free (sorted_env);
}

void	get_new_env(char **new_key, char **new_value, char *arg_str)
{
	int		len;

	while (arg_str[len] != '=' && arg_str[len] != '\0')
			len++;
	*new_key = (char *)malloc(sizeof(char) * len + 1);
	if (!*new_key)
	{
		//error
	}
	ft_strlcpy(*new_key, arg_str, len + 1);
	if (arg_str[len] == '\0')
		*new_value = NULL;
	else
	{
		*new_value = (char *)malloc(sizeof(char) * (ft_strlen(arg_str) - len));
		if (!*new_value)
		{
			//error
		}
		ft_strlcpy(*new_value, arg_str + len + 1, ft_strlen(arg_str) - len);
	}
}

t_env	*is_already_exist(char *new_key, t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (strncmp(new_key, temp->key, ft_strlen(new_key)) == 0)
			break ;
		temp = temp->next;
	}
	return (temp);
}

void	puttt(char *new_key, char *new_value, t_env *env)
{
	t_env	*temp;

	temp = is_already_exist(new_key, env);
	if (!temp)
	{
		temp = env;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = (t_env *)malloc(sizeof(t_env));
		if (!temp->next)
		{
			//error
		}
		temp->next->key = new_key;
		temp->next->value = new_value;
		temp->next->next = NULL;
	}
	else if (new_value)
	{
		free (temp->value);
		temp->value = new_value;
	}
}
/*
	key와 value값 찾아 오는거 - 함수 하나
	대조해서 같은거 있는지 검사
	없으면 마지막 노드
	있으면 해당 노드 - 함수 하나
	넣는 작업 (있으면 free하고 넣어주는거 잊지 말기)
*/
void	put_new_env(t_env *env, t_list *arguments)
{
	t_list	*arg_ptr;
	char	*arg_str;
	char	*new_key;
	char	*new_value;

	arg_ptr = arguments;
	while (arg_ptr != NULL)
	{
		arg_str = (char *)arg_ptr->content;
		get_new_env(&new_key, &new_value, arg_str);
		puttt(new_key, new_value, env);
		arg_ptr = arg_ptr->next;
	}
}

// void	put_new_env(t_env *env, t_list *arguments)
// {
// 	char	*scan;
// 	t_env	*temp;
// 	int		len;
// 	t_list	*arg_temp;

// 	arg_temp = arguments;
// 	while (arg_temp != NULL)
// 	{
// 		temp = env;
// 		while (temp->next != NULL)
// 			temp = temp->next;
// 		len = 0;
// 		scan = (char *)arg_temp->content;
// 		temp->next = (t_env *)malloc(sizeof(t_env));
// 		if (!temp->next)
// 		{
// 			//error
// 		}
// 		temp = temp->next;
// 		temp->next = NULL;
// 		while (scan[len] != '=' && scan[len] != '\0')
// 			len++;
// 		temp->key = (char *)malloc(sizeof(char) * len + 1);
// 		if (!temp->key)
// 		{
// 			//error
// 		}
// 		ft_strlcpy(temp->key, scan, len + 1);
// 		if (!scan[len])
// 			temp->value = NULL;
// 		else
// 		{
// 			temp->value = (char *)malloc(sizeof(char) * (ft_strlen(scan) - len));
// 			if (!temp->value)
// 			{
// 				//error
// 			}
// 			ft_strlcpy(temp->value, scan + len + 1, ft_strlen(scan) - len);
// 		}
// 		arg_temp = arg_temp->next;
// 	}
// }

int	mini_export(t_info *info, t_process *process)
{
	if (!process->arguments)
		print_export(info->env);
	else
		put_new_env(info->env, process->arguments);
	return (exit_process(info, 0));
}
