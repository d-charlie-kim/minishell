# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaejeong <jaejeong@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/03 15:34:43 by jaejeong          #+#    #+#              #
#    Updated: 2021/12/13 18:03:24 by jaejeong         ###   ########.fr        #
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
			  program

vpath %.c	= $(SRCDIR) $(SRCDIR)/$(SUBDIR)
SRCS		= main.c\
			  parse_env.c\
			  split_line_to_process.c\
			  split_process_to_token.c\
			  replace_env_value.c\
			  save_token_in_struct.c\
			  split_utils.c\
			  redirection.c\
			  utils.c\
			  #execute_instruction.c

OBJS		= $(SRCS:.c=.o) # 오브젝트 파일 build 디렉토리로 들어가도록 수정

LIBNAME		= ft
LIB			= $(LIBDIR)/libft.a

all			: $(NAME)

$(NAME)		: $(LIB) $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(INCFLAGS) -L$(LIBDIR) -l$(LIBNAME) -lreadline

$(LIB)		:
	make -C $(LIBDIR) bonus

%.o:		%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCFLAGS) -o $@ -c $^

$(OBJDIR)	:
	mkdir build

clean		:
	$(RM) $(OBJS)
	make -C $(LIBDIR) clean

fclean		: clean
	$(RM) $(NAME)
	make -C $(LIBDIR) fclean

re			: fclean all

.PHONY		: all clean fclean re
