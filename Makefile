# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/03 15:34:43 by dokkim	           #+#    #+#              #
#    Updated: 2022/02/10 00:08:36 by jaejeong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= gcc
CFLAGS		= $(INCFLAGS) $(WFLAGS) #$(GFLAGS)
WFLAGS		= -Wall -Wextra -Werror
GFLAGS		= -g -fsanitize=address
INCFLAGS	= -I$(INCDIR)

INCDIR		= includes
LIBDIR		= libft
SRCDIR		= srcs
OBJDIR		= build
SUBDIR		= parse\
			  program\
			  gnl

vpath %.c	= $(SRCDIR)\
			  $(addprefix $(SRCDIR)/, $(SUBDIR))

SRCS		= main.c\
			  parse_env.c\
			  split_line_to_process.c\
			  split_process_to_token.c\
			  replace_env_value.c\
			  save_token_in_struct.c\
			  split_utils.c\
			  redirection.c\
			  utils.c\
			  fork.c\
			  execute.c\
			  program_in_path.c\
			  get_next_line.c\
			  get_next_line_utils.c\
			  signal.c\
			  mini_pwd.c\
			  mini_export.c\
			  mini_unset.c\
			  mini_env.c\
			  mini_echo.c\
			  mini_exit.c\
			  terminal.c\

OBJS		= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

LIBNAME		= ft
LIB			= $(LIBDIR)/libft.a

all			: $(NAME)

$(NAME)		: $(LIB) $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS) -L$(LIBDIR) -l$(LIBNAME) -lreadline

$(LIB)		:
	make -C $(LIBDIR) bonus

$(OBJDIR)/%.o	: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $^

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
