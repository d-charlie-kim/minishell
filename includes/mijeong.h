/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mijeong.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:55:04 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/11 14:33:52 by jaejeong         ###   ########.fr       */
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
# include <errno.h>
# include "libft.h"
# include "parsing.h"

typedef struct s_info
{
	int		process_count;
	int		last_exit_status;
	char	cur_dir[256];
	t_env	*env;
}				t_info;

t_process	*split_line_to_process(const char *str, t_info *info);
void		split_process_to_token(t_process *process, t_info *info, const char *str, int len);
void		save_token_in_struct(t_process *process, char *token, int tag);
char		*replace_env_value(t_info *info, const char *str, int len);
void		parse_envp(t_info *info, char **envp);
int			check_quotes(char c, int in_quotes);
char		*add_character_to_str(char *str, char character);
char		*remove_quotes_in_str(char *str);

char		*get_env_value(t_env *env, const char *key);
void		print_error_and_exit(char *output, int error_num);

# endif
