/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:02:24 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/07 01:15:58 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

int	main(int argc, char **argv, char **envp)
{
	char		*output;
	t_info		info;
	t_process	*processes;

	// 구조체 init
	getcwd(info.cur_dir, 256);
	while (output = readline(info.cur_dir))
	{
		processes = first_split(output, &info);
		processing_instruction(&info, processes);
		getcwd(info.cur_dir, 256);
		free(output);
	}
	return (0);
}
