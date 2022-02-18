/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:45:27 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/19 00:24:25 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

/*
void	print_parsing_data_test(t_process *processes, int process_count)
{

	//this is test function!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

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
*/

void	run_minishell(t_info *info, t_process *processes)
{
	char	*output;

	init_mom_setting(info);
	output = readline("mijeong$ ");
	if (validate_output(info, output))
		return ;
	add_history(output);
	processes = split_line_to_process(output, info);
	if (validate_process(info, processes))
		return ;
	save_heredoc_str(info, processes);
	reset_output_mode(&(info->org_term));
	if (info->process_count == 1 && is_builtin_function(&processes[0]))
		info->last_exit_status = execute_single_builtin(info, &processes[0]);
	else
		fork_main(info, processes);
	free_all(info, processes, output);
}
	/* print_parsing_data_test(processes, info->process_count);  test code */

void	set_shlvl(t_info *info)
{
	int		num;
	char	*value;
	char	*shlvl;

	value = getenv("SHLVL");
	if (!value)
		shlvl = ft_strdup("1");
	else
	{
		num = ft_atoi(value);
		shlvl = ft_itoa(num + 1);
	}
	puttt("SHLVL", shlvl, info->env);
}
