#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

// int	main(void)
// {
// 	pid_t	pid;
// 	int		pipefd[2];
// 	char	buffer[6];
// 	char	*str = "hello";

// 	pipe(pipefd);
// 	pid = fork();
// 	if (pid == 0) // 자식 프로세스
// 	{
// 		close(pipefd[0]);
// 		write(pipefd[1], str, 6);
// 	}
// 	else // 부모 프로세스
// 	{
// 		wait(NULL);
// 		close(pipefd[1]);
// 		read(pipefd[0], buffer, 6);	
// 		printf("buffer : %s\n", buffer);
// 	}
// }


void	ppp(void)
{
	int pipefd[2];
	char buffer[6];

	read(pipefd[0], buffer, 6);
	printf("buffer : %s\n", buffer);
}

int main(void)
{
	int pipefd[2];
	char *str = "world";

	pipe(pipefd);
	write(pipefd[1], str, 6);
	ppp();
	return (0);
}
