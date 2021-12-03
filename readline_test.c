#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	char		*output;

	while (output = readline("test : "))
	{
		add_history(output);
		printf("%s\n", output);
		free(output);
	}
	return (0);
}
