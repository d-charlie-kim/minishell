/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:19:41 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/10 18:55:04 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

int	mini_exit(t_info *info, t_process *process)
{
	int		exit_status;
	char	*arg;

	if (process->arguments && process->arguments->next)
	{
		write(STDERR_FILENO, "bash: exit: too many arguments\n", 31);
		if (info->process_count == 1)
			return (1); // 에러 코드 무엇임
		else
			exit(1); // 에러 코드 무엇임
	}
	if (info->process_count == 1)
		write(1, "exit\n", 5);
	arg = (char *)(process->arguments->content);
	exit_status = ft_atoi(arg);
	exit(exit_status);
}
