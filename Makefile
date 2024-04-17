# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 13:00:13 by elilliu           #+#    #+#              #
#    Updated: 2024/04/16 15:32:34 by elilliu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

INCLUDE = pipex.h

SRC = main.c utils.c find_paths.c children.c utils2.c

LIBFT_DIR = libft

LIBFT_PATH = libft/libft.a

OBJ_DIR = objects

OBJ = ${addprefix ${OBJ_DIR}/, ${SRC:.c=.o}}

CC = cc

CFLAGS = -Wall -Wextra -Werror

${OBJ_DIR}/%.o: %.c ${INCLUDE}
		mkdir -p ${OBJ_DIR}
		${CC} -c $< -o $@ -g3

${NAME}: ${OBJ} ${LIBFT_PATH}
		${CC} ${OBJ} -o $@ -L${LIBFT_DIR} -lft

${LIBFT_PATH}:
		${MAKE} -C ${LIBFT_DIR} bonus

all: ${NAME}

clean:
		${MAKE} -C ${LIBFT_DIR} clean
		rm -rf ${OBJ} ${OBJ_DIR}

fclean: clean;
		${MAKE} -C ${LIBFT_DIR} fclean
		rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re ${OBJ_DIR}
