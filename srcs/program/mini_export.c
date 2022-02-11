/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:19:39 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/11 16:55:59 by dokkim           ###   ########.fr       */
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
		sorted_env = sorted_env->next;
		free (temp);
	}
	free (sorted_env);
}

void	get_new_env(char **new_key, char **new_value, char *arg_str)
{
	int		len;

	len = 0;
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
		if (env_is_valid(new_key))
			puttt(new_key, new_value, env);
		else
		{
			write(STDERR_FILENO, "bash: export: `", 15);
			write(STDERR_FILENO, new_key, ft_strlen(new_key));
			if (new_value)
			{
				write(STDERR_FILENO, "=", 1);
				write(STDERR_FILENO, new_value, ft_strlen(new_value));
			}
			write(STDERR_FILENO, "\': not a valid identifier\n", 26);
		}
		arg_ptr = arg_ptr->next;
	}
}

int	mini_export(t_info *info, t_process *process)
{
	char	*option;

	if(process->option)
	{
		option = (char *)(process->option->content);
		write(STDERR_FILENO, "bash: export: -", 15);
		write(STDERR_FILENO, &(option[1]), 1);
		write(STDERR_FILENO, ": invalid option\n", 17);
		return (exit_process(info, 1));
	}
	else if (!process->arguments)
		print_export(info->env);
	else
		put_new_env(info->env, process->arguments);
	return (exit_process(info, 0));
}
