/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:45:41 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/19 12:47:08 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"

void	print_error_and_exit(char *output, int error_num)
{
	ft_putstr_fd(output, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(error_num);
}

int	err_option(char	*inst, t_info *info, t_process *process)
{
	char	*option;

	option = (char *)(process->option->content);
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(inst, STDERR_FILENO);
	ft_putstr_fd(": -", STDERR_FILENO);
	ft_putchar_fd(option[1], STDERR_FILENO);
	ft_putstr_fd(": invalid option\n", STDERR_FILENO);
	return (exit_process(info, process, 1));
}
