/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mijeong.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:55:04 by dokkim            #+#    #+#             */
/*   Updated: 2022/02/19 17:17:33 by dokkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MIJEONG_H
# define MIJEONG_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
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
	unsigned char	last_exit_status;
	int				process_count;
	t_env			*env;
	struct termios	org_term;
	struct termios	new_term;
}				t_info;

t_process	*split_line_to_process(const char *str, t_info *info);
int			split_process_to_token(t_process *process, t_info *info, \
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
char		**setting_argv(t_process *process);
char		**setting_envp(t_env *env);
void		find_instruction(t_info *info, t_process *process);
int			execute_program(t_info *info, t_process *cur_process);
void		fork_main(t_info *info, t_process *processes);

void		set_output_redirect(t_process *process);
void		set_input_redirect(t_process *process);

int			mini_exit(t_info *info, t_process *process);
int			mini_echo(t_info *info, t_process *process);
int			mini_pwd(t_info *info, t_process *process);
int			mini_export(t_info *info, t_process *process);
int			mini_env(t_info *info, t_process *process);
int			mini_unset(t_info *info, t_process *process);
int			mini_cd(t_info *info, t_process *process);

void		init_mom_setting(t_info *info);
void		sigint_handler(void);

void		set_output_mode(struct termios *new_term);
void		reset_output_mode(struct termios *org_term);

int			hreredoc_handler(t_info *info, t_process *processes);
int			exit_process(t_info *info, t_process *processes, int exit_status);
int			env_is_valid(char *target);

int			str_is_num(char *arg);

int			err_option(char	*inst, t_info *info, t_process *process);

void		put_new_node_to_sorted_env(t_env *sorted_env, t_env *new_node);
t_env		*init_new_node(t_env *temp);
t_env		*make_sorted_env(t_env *env);
void		print_export(t_env *env);

void		sig_exit_handler(int sig);
void		quit_handler(t_info *info);
void		puttt(char *new_key, char *new_value, t_env *env);
t_env		*is_already_exist(char *new_key, t_env *env);
void		parsing_error_print(char *str);

int			input_delete_space(char *str);
void		free_all(t_info *info, t_process *processes, char *output);

void		print_error_and_exit(char *output, int error_num);
int			err_option(char	*inst, t_info *info, t_process *process);
int			execute_single_builtin(t_info *info, t_process *process);
void		run_minishell(t_info *info, t_process *processes);
void		set_shlvl(t_info *info);

int			validate_output(t_info *info, char *output);
int			validate_process(t_info *info, t_process *processes);
void		free_envp(t_info *info);
void		free_process(t_process *process);

int			heredoc_handler(t_info *info, t_process *processes);
void		save_str(char **save, char *output);

#endif
