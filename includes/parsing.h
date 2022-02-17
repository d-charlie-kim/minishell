/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:54:02 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/17 12:24:00 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define NOT 0  // define quotes
# define SINGLE 1
# define DOUBLE 2

# define SINGLE_IN 1 // define redirection
# define DOUBLE_IN 2
# define SINGLE_OUT 3
# define DOUBLE_OUT 4

# define INST 1 // define tag
# define OPTION 2
# define ARG 3
# define REDIRECTION 4
# define FILENAME 5

typedef struct s_redirect_pair
{
	int		symbol;
	char	*file_name;
}				t_redirect_pair;

typedef struct s_process
{
	pid_t		pid;
	char		*instruction;
	t_list		*option;
	t_list		*arguments;
	t_list		*redirect;
}				t_process;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

#endif
