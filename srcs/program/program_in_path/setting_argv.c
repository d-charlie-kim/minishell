/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 12:31:27 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/19 12:37:33 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

static int	get_argv_size(t_list *option, t_list *arguments)
{
	int	argv_size;

	argv_size = 1 + ft_lstsize(option) + ft_lstsize(arguments);
	return (argv_size);
}

static void	add_option_in_argv(t_list *option, char ***argv)
{
	int	i;

	i = 1;
	while (option)
	{
		(*argv)[i] = (char *)(option->content);
		i++;
		option = option->next;
	}
}

static void	add_arguments_in_argv(t_list *arguments, char ***argv)
{
	int	i;

	i = 1;
	while ((*argv)[i])
		i++;
	while (arguments)
	{
		(*argv)[i] = (char *)(arguments->content);
		i++;
		arguments = arguments->next;
	}
}

char	**setting_argv(t_process *process)
{
	int		argv_size;
	char	**argv;

	argv_size = get_argv_size(process->option, process->arguments);
	argv = (char **)malloc(sizeof(char *) * (argv_size + 1));
	if (!argv)
		print_error_and_exit("cannot allocate memory\n", ENOMEM);
	ft_bzero(argv, sizeof(char *) * (argv_size + 1));
	argv[0] = process->instruction;
	add_option_in_argv(process->option, &argv);
	add_arguments_in_argv(process->arguments, &argv);
	return (argv);
}
