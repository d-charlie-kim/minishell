/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:47:22 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/02 19:25:14 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

#define PATH_MAX 4096

// PATH_MAX 는 linux 에서는 <linux/limits.h>에, 
// mac os 에서는 <sys/syslimits.h>에 정의되어있다.
// 모든 os 에서 작동하게 할 수 있는 방법은 아직 모르겠다....

void	mini_pwd(t_info *info, t_process *process)
{
	char	buf[PATH_MAX];
	char	*option;

	(void)info;
	getcwd(buf, PATH_MAX);
	if (!process->option)
	{
		write(STDOUT_FILENO, buf, ft_strlen(buf));
		write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
	option = (char *)(process->option->content);
	write(STDERR_FILENO, "bash: pwd: -", 12);
	write(STDERR_FILENO, &(option[1]), 1);
	write(STDERR_FILENO, ": invalid option\n", 17);
	exit(1);
}
