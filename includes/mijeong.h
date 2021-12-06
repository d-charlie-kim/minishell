/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mijeong.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:55:04 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/06 16:03:59 by jaejeong         ###   ########.fr       */
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

typedef struct s_info
{
	int		process_count;
	char	cur_dir[256];
}	t_info;

typedef struct s_process
{
	int		token_count;
	char	*instruction;
	char	*option; // option이 여러 개인 경우가 있음. char * 에서 char ** 로?
	char	**bundle;
}	t_process;

# endif

a | < | b

a<b
a    <    b = 3
a<    b     = 2
a    <b     = 2
a    <<b    = 2
a<<b        = 2
a<<    b    = 2
a    <<    b = 


a<"bb"c
a<bbc