#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

int	main(void)
{
	int		status;
	pid_t	ret;
	pid_t	pid_p, pid_c;

	pid_p = getpid();
	printf("부모 프로세스의 pid : %d\n", pid_p);
	ret = fork();
	if (ret > 0)
	{
		pid_c = ret;
		printf("자식 프로세스의 pid : %d\n", pid_c);
	}
	if (getpid() == pid_p)
		usleep(1);
	printf("1. pid : %d\n", getpid());
	printf("2. pid : %d\n", getpid());
	printf("3. pid : %d\n", getpid());
	if (ret == 0)
		sleep(10);
	printf("4. pid : %d\n", getpid());
	printf("5. pid : %d\n", getpid());
}
