#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdlib.h>

struct termios org_term;
struct termios new_term;

void	sigint_handler(void)
{
	// rl_on_new_line();
	// rl_redisplay();
	write(STDIN_FILENO, "\n", 1);  // 다음줄로 넘어간다.
	rl_on_new_line();  // 새로운 줄입니다 라는 것을 readline 함수에게 인식시킨다.
	rl_replace_line("", 0);  //현재 줄에 출력된 것(입력된 것?)을 앞 ""으로 바꿔준다.
	rl_redisplay();  // test test : 기본 str 문구가 없으면 출력한다.
}

void	sigint_handler2(void)
{
	printf("!!!!!\n");
}

void	ft_signal(void)
{
	signal(SIGINT, (void *)sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void save_input_mode(void)
{
	tcgetattr(STDIN_FILENO, &org_term); // STDIN으로부터 터미널 속성을 받아온다
}

void set_input_mode(void)
{
	tcgetattr(STDIN_FILENO, &new_term); // STDOUT으로부터 터미널 속성을 받아온다
	new_term.c_lflag &= ~(ECHOCTL);  // ECHOCTL 속성을 off
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term); // 변경된 속성의 터미널을 STDIN에 바로 적용
}

void reset_input_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &org_term);  // STDIN에 기존의 터미널 속성을 바로 적용
}

int main(void)
{
	int ch = 0;
	char *output;
	
	save_input_mode();       // 터미널 세팅 저장
	set_input_mode();        // 터미널 세팅 변경
	signal(SIGINT, (void *)sigint_handler2);
	ft_signal();
	while (1)
	{
		output = readline("\033[32mminishell $ \033[36m");
		if (!output)
			exit(0);
		add_history(output);
		printf(":::: %s\n", output);
		if (ch == 4)
			break ;
		ch = 0;
	}
	reset_input_mode();      // 터미널 세팅 초기화
	return (0);
}
