/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:34:32 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/07 19:45:17 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mijeong.h"

int	mini_echo(t_info *info, t_process *process)
{
	int		i;
	t_list	*temp;

	i = 0;
	temp = process->arguments;
	while (temp != NULL)
	{
		printf("%s", (char*)temp->content);
		temp = temp->next;
		if (temp != NULL)
			printf(" ");
	}
	printf("\n");
	return (ret_handler(info, exit_status));
}