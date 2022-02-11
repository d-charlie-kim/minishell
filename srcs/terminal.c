/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:38:35 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/11 20:32:09 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include "mijeong.h"

void	save_input_mode(struct termios org_term)
{
	tcgetattr(STDIN_FILENO, &org_term);
}

void	set_input_mode(struct termios new_term)
{
	tcgetattr(STDIN_FILENO, &new_term);
	new_term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

void	reset_input_mode(struct termios org_term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &org_term);
}

void	quit_handler(void)
{
	write(1, "\033[1A", 5);
	write(1, "\033[9C", 5);
	write(1, "exit\n", 5);
	exit(0);
}

/*
		tcgetattr(STDIN_FILENO, &org_term); 
			// STDIN으로부터 터미널 속성을 받아온다 (초기화 용도)

		tcgetattr(STDIN_FILENO, &new_term); 
			// STDOUT으로부터 터미널 속성을 받아온다
		new_term.c_lflag &= ~(ECHOCTL);  
			// ECHOCTL 속성을 off
		tcsetattr(STDIN_FILENO, TCSANOW, &new_term); 
			// 변경된 속성의 터미널을 STDIN에 바로 적용

		tcsetattr(STDIN_FILENO, TCSANOW, &org_term); 
			// STDIN에 기존의 터미널 속성을 바로 적용 (ECHOCTL 속성 바꾸기 전으로 초기화)
*/