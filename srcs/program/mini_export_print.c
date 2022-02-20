/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:13:42 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/20 15:11:50 by dokkim           ###   ########.fr       */
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
		if (ft_strncmp(front_node->key, new_node->key, \
		ft_strlen(front_node->key) + 1) > 0)
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

t_env	*init_new_node(t_env *temp)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		print_error_and_exit("cannot allocate memory\n", ENOMEM);
	new_node->key = temp->key;
	new_node->value = temp->value;
	new_node->next = NULL;
	return (new_node);
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
		print_error_and_exit("cannot allocate memory\n", ENOMEM);
	sorted_env->next = NULL;
	while (temp != NULL)
	{
		new_node = init_new_node(temp);
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
	while (sorted_env != NULL)
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
		sorted_env = sorted_env->next;
		free (temp);
	}
	free (sorted_env);
}
