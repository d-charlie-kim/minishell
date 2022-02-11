/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:47:22 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/11 21:31:41 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

// PATH_MAX 는 linux 에서는 <linux/limits.h>에, 
// mac os 에서는 <sys/syslimits.h>에 정의되어있다.
// 모든 os 에서 작동하게 할 수 있는 방법은 아직 모르겠다....

int	mini_pwd(t_info *info, t_process *process)
{
	char	buf[PATH_MAX];

	(void)info;
	getcwd(buf, PATH_MAX);
	if (!process->option)
	{
		ft_putstr_fd(buf, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (exit_process(info, 0));
	}
	else
		return (err_option("pwd", info, process));
}
