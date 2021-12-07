/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 04:46:22 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/08 04:47:19 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

char *find_env(char *str, t_env *env)
{
	t_env *temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strcmp(str, temp->key))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

int	env_size_check(char *ptr, int size, t_env *env)
{
	int		i;
	int		count;
	int		env_size;
	char	*envp;
	char	*temp;

	i = 0;
	count = 0;
	env_size = 0;
	while (i < size)
	{
		if (ptr[i] == '$' && ptr[i + 1] != ' ')
		{
			i++;
			while (ptr[i] != ' ')
			{
				i++;
				count++;
			}
			temp = (char *)malloc(sizeof(char) * count + 1);
			ft_putncpy(&temp, ptr, i - count, count);
			envp = find_env(temp, env);
			free (temp);
			env_size += ft_strlen(envp);
		}
		else
			i++;
	}
	return (env_size);
}

void	put_process_with_env(char **dest, char *ptr, int size, t_env *env)
{
	int		i;
	int		count;
	char	*envp;
	char	*temp;

	i = 0;
	count = 0;
	while (i < size)
	{
		if (ptr[i] == '$' && ptr[i + 1] != ' ')
		{
			i++;
			while (ptr[i] != ' ')
			{
				i++;
				count++;
			}
			temp = (char *)malloc(sizeof(char) * count + 1);
			ft_putncpy(&temp, ptr, i - count, count);
			envp = find_env(temp, env);
			free (temp);
			ft_putncpy(&dest, envp, 0, ft_strlen(envp));
		}
		else
		{
			*dest = ptr[i];
			i++;
			*dest++;
		}
	}
}
