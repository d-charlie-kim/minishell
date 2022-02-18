/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:02:24 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/18 20:08:07 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

int	main(int argc, char **argv, char **envp)
{
	t_info		info;
	t_process	*processes;

	(void)argc;
	(void)argv;
	info.last_exit_status = 0;
	processes = NULL;
	parse_envp(&info, envp);
	set_shlvl(&info);
	while (1)
		run_minishell(&info, processes);
	return (0);
}
