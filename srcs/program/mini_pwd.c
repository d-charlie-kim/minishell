/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:47:22 by jaejeong          #+#    #+#             */
/*   Updated: 2022/01/13 19:50:17 by jaejeong         ###   ########.fr       */
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

	getcwd(buf, PATH_MAX);
	write(STDOUT_FILENO, buf, ft_strlen(buf) + 1);
}
