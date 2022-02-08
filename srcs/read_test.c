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
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signal(void)
{
	signal(SIGINT, (void *)sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void save_input_mode(void)
{
	tcgetattr(STDOUT_FILENO, &org_term); // STDIN으로부터 터미널 속성을 받아온다
}

// new_term에 원하는 터미널 속성 설정
void set_input_mode(void)
{
	tcgetattr(STDOUT_FILENO, &new_term); // STDIN으로부터 터미널 속성을 받아온다
	new_term.c_lflag &= ~(ECHOCTL);  // ICANON, ECHO 속성을 off
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term); // 변경된 속성의 터미널을 STDIN에 바로 적용
}

void reset_input_mode(void)
{
	tcsetattr(STDOUT_FILENO, TCSANOW, &org_term);  // STDIN에 기존의 터미널 속성을 바로 적용
}

int main(void)
{
	int ch = 0;
	char *output;
	
	save_input_mode();       // 터미널 세팅 저장
	// set_input_mode();        // 터미널 세팅 변경
	ft_signal();
	while (1)
	{
		output = readline("test test : ");
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