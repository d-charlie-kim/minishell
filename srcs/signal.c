/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:38:40 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/18 20:22:12 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "mijeong.h"

void	sig_exit_handler(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\n", STDOUT_FILENO);
	else if (sig == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
}

void	sigint_handler(void)
{
	write(STDERR_FILENO, "\b\b", 2);
	write(STDERR_FILENO, "  \n", 3);
	ft_putstr_fd("mijeong$ ", STDERR_FILENO);
	// rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
}

void	init_mom_setting(t_info *info)
{
	(void)info;
	signal(SIGINT, (void *)sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	set_output_mode(&(info->new_term));
}

/*
	write(STDIN_FILENO, "\n", 1);  // 다음줄로 넘어간다.
	rl_on_new_line();  // 새로운 줄입니다 라는 것을 readline 함수에게 인식시킨다.
	rl_replace_line("", 0);  //현재 줄에 출력된 것(입력된 것?)을 앞 ""으로 바꿔준다.
	rl_redisplay();  // test test : 기본 str 문구가 없으면 출력한다.
*/
