#include <signal.h>
#include "mijeong.h"

void	sigint_handler(void)
{
	write(1, "!!!!\n", 5);
	write(1, "mijeong$ ", 9);
}

void	sigquit_handler(void)
{
	write(1, "\b\b", 2);
	write(1, "mijeong$ ", 9);
}

void	ft_signal(void)
{
	signal(SIGINT, (void *)sigint_handler);
	signal(SIGQUIT, (void *)sigquit_handler);
}
