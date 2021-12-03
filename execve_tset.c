#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	char	*argv[2] = {"env", NULL};
	char	*envp[4] = {"test1=abc", "test2=def", "asdf=fdsa", NULL};
		
	execve("./print_env", argv, envp);
}
