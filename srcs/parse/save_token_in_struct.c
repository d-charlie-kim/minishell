/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_token_in_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:58:33 by jaejeong          #+#    #+#             */
/*   Updated: 2021/12/10 17:33:38 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

static void	save_redirect(t_process *process, const char *str)
{
	t_list			*new_node;
	t_redirect_pair	*pair;

	new_node = (t_list *)malloc(sizeof(t_list));
	pair = (t_redirect_pair *)malloc(sizeof(t_redirect_pair));
	if (!pair || !new_node)
		print_error_and_exit("cannot allocate memory\n", ENOMEM);
	pair->file_name = NULL;
	if (str[0] == '<' && str[1] == '\0')
		pair->symbol = SINGLE_IN;
	else if (str[0] == '>' && str[1] == '\0')
		pair->symbol = SINGLE_OUT;
	else if (str[0] == '<' && str[1] == '<' && str[2] == '\0')
		pair->symbol = DOUBLE_IN;
	else if (str[0] == '>' && str[1] == '>' && str[2] == '\0')
		pair->symbol = DOUBLE_OUT;
	free(str);
	new_node->content = (void *)pair;
	new_node->next = NULL;
	ft_lstadd_back(&(process->redirect), new_node);
}

static void	save_filename(t_process *process, const char *str)
{
	t_list			*temp;
	t_redirect_pair	*pair;
	
	temp = ft_lstlast(process->redirect);
	pair = (t_redirect_pair *)temp->content;
	pair->file_name = str;
}

static void	save_option(t_process *process, const char *token)
{
	t_list	*new_node;
		
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		print_error_and_exit("cannot allocate memory\n", ENOMEM);
	new_node->content = (void *)token;
	new_node->next = NULL;
	ft_lstadd_back(&(process->option), new_node);
}

static void	save_argument(t_process *process, const char *token)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		print_error_and_exit("cannot allocate memory\n", ENOMEM);
	new_node->content = (void *)token;
	new_node->next = NULL;
	ft_lstadd_back(&(process->arguments), new_node);
}

void	save_token_in_struct(t_process *process, const char *token, int tag)
{
	if (!token)
		return ;
	if (tag == INST)
		process->instruction = token;
	else if (tag == REDIRECTION)
		save_redirect(process, token);
	else if (tag == FILENAME)
		save_filename(process, token);
	else if (tag == OPTION)
		save_option(process, token);
	else if (tag == ARG)
		save_argument(process, token);
}
