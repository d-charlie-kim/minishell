/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:54:02 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/06 18:14:37 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SPLIT_H
# define MINI_SPLIT_H

# define SINGLE_IN 1
# define DOUBLE_IN 2
# define SINGLE_OUT 3
# define DOUBLE_OUT 4

typedef struct s_redirect
{
	int		symbol; // < : SINGLE_IN, << : DOUBLE_IN, > : SINGLE_OUT, >> : DOUBLE_OUT
	char	file_name[256];
}				t_redirect;

typedef struct s_process
{
	char		*instruction;
	char		**arguments;
	char		**options; // option이 여러 개인 경우가 있음. char * 에서 char ** 로?
	t_redirect	*input;
	t_redirect	*output;

	int		token_count;
	char	**bundle;
}				t_process;

#endif
