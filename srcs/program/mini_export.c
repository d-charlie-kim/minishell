/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:19:39 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/20 15:11:38 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"
#include "libft.h"

void	get_new_env(char **new_key, char **new_value, char *arg_str)
{
	int		len;

	len = 0;
	while (arg_str[len] != '=' && arg_str[len] != '\0')
		len++;
	*new_key = (char *)malloc(sizeof(char) * len + 1);
	if (!*new_key)
		print_error_and_exit("cannot allocate memory\n", ENOMEM);
	ft_strlcpy(*new_key, arg_str, len + 1);
	if (arg_str[len] == '\0')
		*new_value = NULL;
	else
	{
		*new_value = (char *)malloc(sizeof(char) * (ft_strlen(arg_str) - len));
		if (!*new_value)
			print_error_and_exit("cannot allocate memory\n", ENOMEM);
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
			print_error_and_exit("cannot allocate memory\n", ENOMEM);
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
			ft_putstr_fd("bash: export: `", STDERR_FILENO);
			ft_putstr_fd(new_key, STDERR_FILENO);
			if (new_value)
			{
				ft_putstr_fd("=", STDERR_FILENO);
				ft_putstr_fd(new_value, STDERR_FILENO);
			}
			ft_putstr_fd("\': not a valid identifier\n", STDERR_FILENO);
		}
		arg_ptr = arg_ptr->next;
	}
}

int	mini_export(t_info *info, t_process *process)
{
	if (process->option)
		return (err_option("export", info, process));
	else if (!process->arguments)
		print_export(info->env);
	else
		put_new_env(info->env, process->arguments);
	return (exit_process(info, process, 0));
}
