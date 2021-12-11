/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:02:24 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/11 23:23:07 by jaejeong         ###   ########.fr       */
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
	// signal 처리
	info.env = NULL;
	parse_envp(&info, envp);
	output = readline("mijeong$ ");
	while (output)
	{
		add_history(output);
		processes = split_line_to_process(output, &info);
		print_parsing_data_test(processes, info.process_count);
		//execute_instruction(&info, processes);
		free(output);
		output = readline("mijeong$ ");
	}
	return (0);
}
