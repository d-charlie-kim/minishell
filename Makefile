# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dokkim <dokkim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/03 15:34:43 by dokkim	           #+#    #+#              #
#    Updated: 2022/02/13 16:54:01 by dokkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= gcc
CFLAGS		= $(INCFLAGS) $(WFLAGS)  $(GFLAGS)
WFLAGS		= -Wall -Wextra -Werror
# GFLAGS		= -g -fsanitize=address
INCFLAGS	= -I$(INCDIR)

INCDIR		= includes
LIBDIR		= libft
SRCDIR		= srcs
OBJDIR		= build
SUBDIR		= parse\
			  program\
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
			  save_token_in_struct.c\
			  split_utils.c\
			  \
			  output_redir.c\
			  \
			  utils.c\
			  fork.c\
			  execute.c\
			  program_in_path.c\
			  get_next_line.c\
			  get_next_line_utils.c\
			  signal.c\
			  mini_pwd.c\
			  mini_export.c\
			  mini_export_print.c\
			  mini_unset.c\
			  mini_env.c\
			  mini_echo.c\
			  mini_exit.c\
			  mini_cd.c\
			  terminal.c\
			  heredoc.c\
			  error.c

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
