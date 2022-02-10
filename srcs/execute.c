/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 23:30:22 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/10 15:52:36 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"

int	execute_program(t_info *info, t_process *cur_process)
{
	if (!ft_strncmp("cd", cur_process->instruction, 3))          // together
		return (mini_cd(info, cur_process));
	else if (!ft_strncmp("exit", cur_process->instruction, 5))   // char
		return (mini_exit(info, cur_process));
	else if (!ft_strncmp("env", cur_process->instruction, 4))    // char
		return (mini_env(info, cur_process));
	else if (!ft_strncmp("export", cur_process->instruction, 7)) // char
		return (mini_export(info, cur_process));
	else if (!ft_strncmp("unset", cur_process->instruction, 6)) // char
		return (mini_unset(info, cur_process));
	else if (!ft_strncmp("pwd", cur_process->instruction, 4))   // jae
	 	return (mini_pwd(info, cur_process));
	else if (!ft_strncmp("echo", cur_process->instruction, 5))  // together
		return (mini_echo(info, cur_process));
	else
		return (find_instruction(info, cur_process)); // 명령어가 빈 문자열일 때 아직 처리하지 못함 // jae
											 // ex) echo a | $rtjkgsrgsrth
	 print_error_and_exit("명령어를 찾지 못했어요ㅠㅠ\n", 5555555);
}
