# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/03 15:34:43 by dokkim	           #+#    #+#              #
#    Updated: 2022/02/20 15:59:13 by jaejeong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= gcc
CFLAGS		= $(INCFLAGS) $(WFLAGS) $(GFLAGS)
WFLAGS		= -Wall -Wextra -Werror
GFLAGS		= -g -fsanitize=address
INCFLAGS	= -I$(INCDIR)

INCDIR		= includes
LIBDIR		= libft
SRCDIR		= srcs
OBJDIR		= build
SUBDIR		= parse\
			  program\
			  program/program_in_path\
			  gnl\
			  redirection

RL_LIB_DIR	= ${HOME}/.brew/opt/readline/lib
RL_INC_DIR	= ${HOME}/.brew/opt/readline/include

vpath %.c	= $(SRCDIR)\
			  $(addprefix $(SRCDIR)/, $(SUBDIR))

SRCS		= main.c\
			  \
			  parse_env.c\
			  split_line_to_process.c\
			  split_process_to_token.c\
			  replace_env_value.c\
			  classify_token.c\
			  save_token_in_struct.c\
			  parse_utils.c\
			  \
			  heredoc.c\
			  output_redir.c\
			  input_redir.c\
			  \
			  get_next_line.c\
			  get_next_line_utils.c\
			  get_next_line_utils2.c\
			  \
			  fork.c\
			  execute.c\
			  \
			  mini_pwd.c\
			  mini_export.c\
			  mini_export_print.c\
			  mini_unset.c\
			  mini_env.c\
			  mini_echo.c\
			  mini_exit.c\
			  mini_cd.c\
			  \
			  setting_argv.c\
			  setting_envp.c\
			  program_in_path.c\
			  \
			  signal.c\
			  terminal.c\
			  init_minishell.c\
			  error.c\
			  clear.c\
			  validate.c\
			  utils.c\
			  

OBJS		= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

LIBNAME		= ft
LIB			= $(LIBDIR)/libft.a

all			: $(NAME)

$(NAME)		: $(LIB) $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS) -L$(LIBDIR) -L$(RL_LIB_DIR) -l$(LIBNAME) -lreadline

$(LIB)		:
	make -C $(LIBDIR) bonus

$(OBJDIR)/%.o	: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $^ -I$(RL_INC_DIR)

$(OBJDIR)	:
	mkdir build

clean		:
	$(RM) -r $(OBJDIR)
	make -C $(LIBDIR) clean

fclean		: clean
	$(RM) $(NAME)
	make -C $(LIBDIR) fclean

re			: fclean all

.PHONY		: all clean fclean re
