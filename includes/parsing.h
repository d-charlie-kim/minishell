/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:54:02 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/07 17:12:12 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

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
	char		**options;
	char		**arguments;
	t_redirect	*redirect; // input, output을 나누지 않고 하나로 모아서 나중에 처리
}				t_process;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

#endif
