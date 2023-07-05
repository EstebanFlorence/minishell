# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 21:24:46 by adi-nata          #+#    #+#              #
#    Updated: 2023/05/10 15:15:51 by adi-nata         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	include/libft.a

SRCS	=	srcs/ft_isalpha.c		srcs/ft_isdigit.c\
			srcs/ft_isalnum.c		srcs/ft_isascii.c\
			srcs/ft_isprint.c		srcs/ft_tolower.c\
			srcs/ft_toupper.c		srcs/ft_memset.c\
			srcs/ft_bzero.c			srcs/ft_memcpy.c\
			srcs/ft_memcmp.c		srcs/ft_memmove.c\
			srcs/ft_memchr.c		srcs/ft_strlen.c\
			srcs/ft_strlcpy.c		srcs/ft_strncmp.c\
			srcs/ft_strchr.c		srcs/ft_strnstr.c\
			srcs/ft_atoi.c			srcs/ft_calloc.c\
			srcs/ft_strdup.c		srcs/ft_strrchr.c\
			srcs/ft_strlcat.c		srcs/ft_substr.c\
			srcs/ft_strjoin.c		srcs/ft_strtrim.c\
			srcs/ft_strmapi.c		srcs/ft_striteri.c\
			srcs/ft_putchar.c		srcs/ft_putchar_fd.c\
			srcs/ft_putstr.c		srcs/ft_putstr_fd.c\
			srcs/ft_putendl_fd.c	srcs/ft_putnbr.c\
			srcs/ft_putnbr_fd.c		srcs/ft_strcmp.c\
			srcs/ft_itoa.c			srcs/ft_lstnew.c\
			srcs/ft_lstadd_front.c	srcs/ft_lstsize.c\
			srcs/ft_lstlast.c		srcs/ft_lstadd_back.c\
			srcs/ft_lstdelone.c		srcs/ft_lstclear.c\
			srcs/ft_lstiter.c		srcs/get_next_line.c\
			srcs/ft_atol.c			srcs/ft_atof.c\
			\
			ft_printf/ft_printf.c\
			ft_printf/syntax.c\
			ft_printf/checkflags.c\
			ft_printf/printftools1.c\
			ft_printf/printftools2.c\
			ft_printf/printftools3.c\
			ft_printf/printf_c.c\
			ft_printf/printf_s.c\
			ft_printf/printf_p.c\
			ft_printf/printf_di.c\
			ft_printf/printf_u.c\
			ft_printf/printf_x.c

OBJS	=	${SRCS:.c=.o}

CC		=	gcc

RM		=	rm -f

FLAGS	=	-g -Wall -Wextra -Werror -Iinclude/



${NAME}:	${OBJS}

			@ar rcs ${NAME} ${OBJS}

all:		${NAME}

.c.o:
			@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

clean:
			@${RM} *.o */*.o */*/*.o

fclean:		clean
			@${RM} ${NAME}

re:			fclean all


.PHONY:			all clean fclean re bonus bonusclean bonusfclean bonusre
