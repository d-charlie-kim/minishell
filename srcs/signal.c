/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:38:40 by jaejeong          #+#    #+#             */
/*   Updated: 2022/02/13 19:10:02 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "mijeong.h"

void	sigint_handler_mom(void)
{
	rl_on_new_line();
	rl_redisplay();
	write(STDIN_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler_child(void)
{
	write(1, "\n", 1);
}

void	sigquit_handler_child(void)
{
	write(1, "exit\n", 5);
	exit(0);
}

void	init_mom_setting(t_info *info)
{
	save_output_mode(info->org_term);
	set_output_mode(info->new_term);
	signal(SIGINT, (void *)sigint_handler_mom);
	signal(SIGQUIT, SIG_IGN);
}

void	init_child_setting(t_info *info)
{
	(void)info;
	signal(SIGINT, (void *)sigint_handler_child);
	signal(SIGQUIT, (void *)sigquit_handler_child);
}

/*
	write(STDIN_FILENO, "\n", 1);  // 다음줄로 넘어간다.
	rl_on_new_line();  // 새로운 줄입니다 라는 것을 readline 함수에게 인식시킨다.
	rl_replace_line("", 0);  //현재 줄에 출력된 것(입력된 것?)을 앞 ""으로 바꿔준다.
	rl_redisplay();  // test test : 기본 str 문구가 없으면 출력한다.
*/