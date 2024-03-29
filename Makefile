# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 14:22:56 by adi-nata          #+#    #+#              #
#    Updated: 2023/09/28 21:10:28 by adi-nata         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

SRC_DIR		=	src

OBJ_DIR		=	.obj

SRCS		=   ${SRC_DIR}/minishell.c\
\
				${SRC_DIR}/tools/tools.c						${SRC_DIR}/tools/lexer_innit.c\
				${SRC_DIR}/tools/parser_innit.c					${SRC_DIR}/tools/pipe_split.c\
				${SRC_DIR}/tools/pipe_numstr.c					${SRC_DIR}/tools/free.c\
				${SRC_DIR}/tools/signal.c\
\
				${SRC_DIR}/parser/parser.c						${SRC_DIR}/parser/parser_tools.c\
\
				${SRC_DIR}/parser/lexer/lexer.c					${SRC_DIR}/parser/lexer/lex_tools.c\
				${SRC_DIR}/parser/lexer/lex_state_normal.c		${SRC_DIR}/parser/lexer/lex_state_quotes.c\
				${SRC_DIR}/parser/lexer/lex_state_dollar.c		${SRC_DIR}/parser/lexer/lex_state_dollarquotes.c\
				${SRC_DIR}/parser/lexer/lex_state_redirect.c\
\
				${SRC_DIR}/parser/expander/expander.c			${SRC_DIR}/parser/expander/expand_tools.c\
				${SRC_DIR}/parser/expander/multiexpand_tools.c\
\
				${SRC_DIR}/redirect/redirect.c					${SRC_DIR}/redirect/redir_open.c\
				${SRC_DIR}/redirect/redir_tools.c\
\
				${SRC_DIR}/executer/execute.c					${SRC_DIR}/executer/exec_tools.c\
\
				${SRC_DIR}/builtins/builtin.c					${SRC_DIR}/builtins/cd.c\
				${SRC_DIR}/builtins/echo.c						${SRC_DIR}/builtins/env.c\
				${SRC_DIR}/builtins/exit.c						${SRC_DIR}/builtins/export.c\
				${SRC_DIR}/builtins/pwd.c						${SRC_DIR}/builtins/unset.c\
				${SRC_DIR}/builtins/utils_builtin.c\


OBJS        =	${patsubst ${SRC_DIR}/%.c,${OBJ_DIR}/%.o,${SRCS}}

CC			=	gcc

RM			=	rm -rf

LIB			=	libft

FLAGS		=	-g -Iinclude/ -Ilibft/include/ -Wall -Wextra -Werror

LIBFLAGS	=	-L./libft/include/ -lft

# Flags for Macs
MACFLAGS	=	-g -Iinclude/ -Ilibft/include/ -Wall -Wextra -Werror -I/usr/local/Cellar/readline/8.2.7/include

LIBMAC		=	-L./libft/include/ -lft -L/usr/local/Cellar/readline/8.2.7/lib


MAKEFLAGS	+=	--silent

CLR_RMV		=	\033[0m
RED		    =	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
CYAN 		=	\033[1;36m


ifeq ($(shell uname), Darwin)
	TRUEFLAGS = ${MACFLAGS}
	TRUELIBS = ${LIBMAC}
else
	TRUEFLAGS = ${FLAGS}
	TRUELIBS = ${LIBFLAGS}
endif


${OBJ_DIR}/%.o:	${SRC_DIR}/%.c
				@mkdir -p ${@D}
				${CC} ${TRUEFLAGS} -c $< -o $@

${NAME}:		${OBJS}
				@echo "${GREEN}Compilation ${CLR_RMV}of ${YELLOW}${LIB} ${CLR_RMV}..."
				@make -C ./libft
				@echo "${GREEN}${LIB} created[0m ✔️"

				@echo "${GREEN}Compilation ${CLR_RMV}of ${YELLOW}${NAME} ${CLR_RMV}..."
				${CC} ${TRUEFLAGS} ${OBJS} ${TRUELIBS} -lreadline -o ${NAME}
				@echo "${GREEN}${NAME} created[0m ✔️"

all:			${NAME}

objs:
				@mkdir -p obj

clean:
				@ echo "${RED}Deleting ${CYAN}${LIB} ${CLR_RMV}libft objs ✔️"
				@make clean -C ./libft

				@ echo "${RED}Deleting ${CYAN}${NAME} ${CLR_RMV}objs ✔️"
				@${RM} ${OBJ_DIR}


fclean:			clean
				@ echo "${RED}Deleting ${CYAN}${LIB} ${CLR_RMV}binary ✔️"
				@make fclean -C ./libft

				@ echo "${RED}Deleting ${CYAN}${NAME} ${CLR_RMV}binary ✔️"
				@${RM} ${NAME}

re:				fclean all

.PHONY:			all clean fclean re bonus
