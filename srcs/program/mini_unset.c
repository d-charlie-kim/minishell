#include "mijeong.h"
#include "parsing.h"

void	first_env_check(t_env *env, char *str)
{
	t_env	*temp;

	temp = env;
	if (ft_strncmp(str, env->key, ft_strlen(str)))
	{
		if (env->next == NULL)
		{
			free (env);
			return ;
		}
		temp = env->next;
		free (env);
		env = temp;
	}

}

void	delete_env(t_env *env, char *str)
{
	t_env	*temp;
	t_env	*previous_temp;


	first_env_check(env, str);
	temp = env->next;
	previous_temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp(str, temp->key, ft_strlen(str)))
		{
			previous_temp->next = temp->next;
			free (temp);
			return ;
		}
		temp = temp->next;
		previous_temp = previous_temp->next;
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