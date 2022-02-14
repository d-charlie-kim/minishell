/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mijeong.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:55:04 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/14 16:38:29 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MIJEONG_H
# define MIJEONG_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <termios.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <limits.h>
# include "libft.h"
# include "parsing.h"
# include "get_next_line.h"

# ifndef PATHMAX
#  define PATHMAX 4096
# endif

typedef struct s_info
{
	int				process_count;
	unsigned char	last_exit_status;
	t_env			*env;
	struct termios	org_term;
	struct termios	new_term;
}				t_info;

t_process	*split_line_to_process(const char *str, t_info *info);
void		split_process_to_token(t_process *process, t_info *info, \
			const char *str, int len);
void		save_token_in_struct(t_process *process, char *token, int tag);
char		*replace_env_value(t_info *info, const char *str, int len);
void		parse_envp(t_info *info, char **envp);
int			check_quotes(char c, int *is_in_quotes);
void		add_character_to_str(char **str, char character);
void		remove_outside_quotes_in_str(char **str);

char		*get_env_value(t_env *env, const char *key);
void		print_error_and_exit(char *output, int error_num);

bool		is_builtin_function(t_process *cur_process);
void		find_instruction(t_info *info, t_process *process);
int			execute_program(t_info *info, t_process *cur_process);
void		fork_main(t_info *info, t_process *processes);

void		set_output_redirect(t_process *process);

int			mini_exit(t_info *info, t_process *process);
int			mini_echo(t_info *info, t_process *process);
int			mini_pwd(t_info *info, t_process *process);
int			mini_export(t_info *info, t_process *process);
int			mini_env(t_info *info, t_process *process);
int			mini_unset(t_info *info, t_process *process);
int			mini_cd(t_info *info, t_process *process);

void		init_child_setting(t_info *info);
void		init_mom_setting(t_info *info);
void		sigquit_handler_child(void);
void		sigint_handler_child(void);
void		sigint_handler_mom(void);

void		save_output_mode(struct termios org_term);
void		set_output_mode(struct termios new_term);
void		reset_output_mode(struct termios org_term);

void		heredoc(t_process *process, int last);
int			exit_process(t_info *info, int exit_status);
int			env_is_valid(char *target);

int			err_option(char	*inst, t_info *info, t_process *process);

void		put_new_node_to_sorted_env(t_env *sorted_env, t_env *new_node);
t_env		*init_new_node(t_env *temp);
t_env		*make_sorted_env(t_env *env);
void		print_export(t_env *env);

void		quit_handler(t_info *info);
void	puttt(char *new_key, char *new_value, t_env *env);
t_env	*is_already_exist(char *new_key, t_env *env);

#endif
