/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:02:24 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/08 01:01:47 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

int	main(int argc, char **argv, char **envp)
{
	char		*output;
	t_info		info;
	t_process	*processes;

	// signal 처리
	// 구조체 init
	parse_env(&info, envp);
	while (output = readline("mijeong$ "))
	{
		add_history(output);
		processes = first_split(output, &info);
		execute_instruction(&info, processes);
		free(output);
	}
	return (0);
}
