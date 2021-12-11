/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:02:24 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/11 14:09:37 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

void	print_parsing_data_test(t_process *processes, int process_count)
{
	t_list	*temp;

	for (int i = 0; i < process_count; i++)
	{
		printf("%d번째 프로세스\n", i);
		printf("명령어 : %s\n", processes[i].instruction);
		printf("옵션 : \n");
		temp = processes[i].option;
		while (!temp)
		{
			char *str = (char *)temp->content;

			printf("%s\n", str);
			temp = temp->next;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*output;
	t_info		info;
	t_process	*processes;

	(void)argc; (void)argv;
	// signal 처리
	// 구조체 init
	parse_envp(&info, envp);
	output = readline("mijeong$ ");
	while (!output)
	{
		add_history(output);
		processes = split_line_to_process(output, &info);
		print_parsing_data_test(processes, info.process_count);
		//execute_instruction(&info, processes);
		free(output);
		readline("mijeong$ ");
	}
	return (0);
}
