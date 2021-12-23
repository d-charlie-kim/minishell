#include "mijeong.h"
#include "parsing.h"

void	delete_env(t_env **env, char *str)
{
	t_env	*temp;
	t_env	*target;
	int		len;

	temp = *env;
	len = ft_strlen(str);
	if (!ft_strncmp(temp->key, str, len + 1))
	{
		temp = temp->next;
		free (*env);
		*env = temp;
		return ;
	}
	while (temp->next != NULL)
	{
		if (!ft_strncmp(temp->next->key, str, len + 1))
		{
			target = temp->next;
			temp = target->next;
			free (target);
			return ;
		}
		temp = temp->next;
	}
}

int	mini_unset(t_info *info, t_process *process)
{
	t_list	*arguments;
	char	*str;
	
	if (!info->env)
		return (0);
	arguments = process->arguments;
	while (arguments != NULL)
	{
		str = (char *)arguments->content;
		delete_env(info->env, str);
		arguments = arguments->next;
	}
}