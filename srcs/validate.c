/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:46:22 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/18 18:49:19 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"
#include "parsing.h"

int	validate_output(t_info *info, char *output)
{
	if (!output)
		quit_handler(info);
	if (output[0] == '\0')
		return (1);
	return (0);
}

int	validate_process(t_info *info, t_process *processes)
{
	int				i;
	t_list			*ptr;
	t_redirect_pair	*redirect_ptr;

	if (!processes)
		return (1);
	i = 0;
	while (i < info->process_count)
	{
		ptr = processes[i].redirect;
		while (ptr)
		{
			redirect_ptr = (t_redirect_pair *)ptr->content;
			if (!redirect_ptr->file_name)
			{
				parsing_error_print("`newline'");
				return (1);
			}
			ptr = ptr->next;
		}
		i++;
	}
	return (0);
}
