/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:54:02 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/06 21:33:37 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SPLIT_H
# define MINI_SPLIT_H

# define SINGLE_IN 1
# define DOUBLE_IN 2
# define SINGLE_OUT 3
# define DOUBLE_OUT 4
# define ERROR 5

typedef struct s_redirect
{
	int		symbol; // < : SINGLE_IN, << : DOUBLE_IN, > : SINGLE_OUT, >> : DOUBLE_OUT, ERROR : 5
	char	file_name[256];
}				t_redirect;

typedef struct s_process
{
	char		**bundle;
	char		*instruction;
	char		**options; // option이 여러 개인 경우가 있음. char * 에서 char ** 로?
	char		**arguments;
	t_redirect	*input;
	t_redirect	*output;
}				t_process;

#endif
