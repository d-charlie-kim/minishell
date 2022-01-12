#include <signal.h>
#include "mijeong.h"

void	sigint_handler(void)
{
	write(1, "\b\b\n\b\b", 5);
}

void	sigquit_handler(void)
{
	write(1, "\b\b", 2);
}

void	ft_signal(void)
{
	signal(SIGINT, (void *)sigint_handler);
	signal(SIGQUIT, (void *)sigquit_handler);
}
