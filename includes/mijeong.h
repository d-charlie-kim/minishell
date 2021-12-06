/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mijeong.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:55:04 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/06 18:14:37 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MIJEONG_H
# define MIJEONG_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "mini_split.h"

typedef struct s_info
{
	int		process_count;
	char	cur_dir[256];
}				t_info;

typedef struct s_list;
{
	int		temp;
	t_list	*next;
}	t_list;

# endif
