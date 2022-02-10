/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:02:24 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/10 20:42:40 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

void	print_parsing_data_test(t_process *processes, int process_count)
{
/**********************************************************************
 * 
	 this is test function!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 
**********************************************************************/
	t_list	*temp;

	for (int i = 0; i < process_count; i++)
	{
		printf("%d번째 프로세스\n", i);
		printf("instruction : %s\n", processes[i].instruction);
		printf("option : \n");
		temp = processes[i].option;
		while (temp)
		{
			char *str = (char *)temp->content;

			printf("%s\n", str);
			temp = temp->next;
		}
		printf("arguments : \n");
		temp = processes[i].arguments;
		while (temp)
		{
			char *str = (char *)temp->content;

			printf("%s\n", str);
			temp = temp->next;
		}
		temp = processes[i].redirect;
		while (temp)
		{
			t_redirect_pair *pair = (t_redirect_pair *)temp->content;

			printf("redirect : %d, filename : %s\n", pair->symbol, pair->file_name);
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
	init_mom_setting(&info);
	info.env = NULL;

	parse_envp(&info, envp);

	while (1)
	{
		output = readline("mijeong$ ");
		if (!output)
		{
			write(1, "exit\n", 5); // 현재 개행이 나오고 exit이 출력됨. 개행이 나오지 않도록 수정
			exit(0);
		}
		if (output[0] == '\0')
			continue ;
		add_history(output);
		processes = split_line_to_process(output, &info);
		// print_parsing_data_test(processes, info.process_count); // test code ##
		if (info.process_count == 1)
			info.last_exit_status = execute_program(&info, &processes[0]);
		else
			fork_main(&info, processes);
		free(output);
	}
	return (0);
}
