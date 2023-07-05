# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 14:22:56 by adi-nata          #+#    #+#              #
#    Updated: 2023/07/06 00:46:35 by adi-nata         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

SRC_DIR		=	src

OBJ_DIR		=	obj

SRCS		=   src/minishell.c		src/tools.c

OBJS		=	${addprefix obj/,${notdir ${SRCS:.c=.o}}}

CC			=	gcc

RM			=	rm -rf

FLAGS		=	-g -Iinclude/ -Ilibft/include/ -Wall -Wextra -Werror

MAKEFLAGS	+=	--silent

LIB			=	libft

LIBFLAGS	=	-L./libft/include -lft

CLR_RMV		=	\033[0m
RED		    =	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
CYAN 		=	\033[1;36m


${OBJ_DIR}/%.o:	${SRC_DIR}/%.c
				@mkdir -p ${OBJ_DIR}
				@${CC} ${FLAGS} -c $< -o $@

${NAME}:		${OBJS}
				@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(LIB) ${CLR_RMV}..."
				@make -C ./libft
				@echo "$(GREEN)$(LIB) created[0m ✔️"

				@echo "${GREEN}Compilation ${CLR_RMV}of ${YELLOW}${NAME} ${CLR_RMV}..."
				@${CC} ${FLAGS} ${OBJS} ${LIBFLAGS} -lreadline -o ${NAME}
				@echo "${GREEN}${NAME} created[0m ✔️"

all:			${NAME}

objs:
				@mkdir -p obj

clean:
				@ echo "$(RED)Deleting $(CYAN)$(LIB) $(CLR_RMV)libft objs ✔️"
				@make clean -C ./libft

				@ echo "${RED}Deleting ${CYAN}${NAME} ${CLR_RMV}objs ✔️"
				@${RM} obj


fclean:			clean
				@ echo "$(RED)Deleting $(CYAN)$(LIB) $(CLR_RMV)binary ✔️"
				@make fclean -C ./libft

				@ echo "${RED}Deleting ${CYAN}${NAME} ${CLR_RMV}binary ✔️"
				@${RM} ${NAME}

re:				fclean all

.PHONY:			all clean fclean re bonus
