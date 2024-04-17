# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 13:00:13 by elilliu           #+#    #+#              #
#    Updated: 2024/04/17 16:52:48 by elilliu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipex_bonus

INCLUDE = pipex.h

SRC = main.c utils.c find_paths.c children.c utils2.c
BONUS = pipex_bonus.c utils.c utils2.c find_paths.c children.c

LIBFT_DIR = libft
LIBFT_PATH = libft/libft.a

OBJ_DIR = objects

OBJ = ${addprefix ${OBJ_DIR}/, ${SRC:.c=.o}}
OBJ_BONUS = ${addprefix ${OBJ_DIR}/, ${BONUS:.c=.o}}

CC = cc
CFLAGS = -Wall -Wextra -Werror

${OBJ_DIR}/%.o: %.c ${INCLUDE}
		mkdir -p ${OBJ_DIR}
		${CC} ${CFLAGS} -c $< -o $@ -g3

${NAME}: ${OBJ} ${LIBFT_PATH}
		${CC} ${CFLAGS} ${OBJ} -o $@ -L${LIBFT_DIR} -lft

${BONUS_NAME}: ${OBJ_BONUS} ${LIBFT_PATH}
		${CC} ${CFLAGS} ${OBJ_BONUS} -o $@ -L${LIBFT_DIR} -lft

${LIBFT_PATH}:
		${MAKE} -C ${LIBFT_DIR} bonus

all: ${NAME}

bonus: ${BONUS_NAME}

clean:
		${MAKE} -C ${LIBFT_DIR} clean
		rm -rf ${OBJ} ${OBJ_BONUS} ${OBJ_DIR}

fclean: clean;
		${MAKE} -C ${LIBFT_DIR} fclean
		rm -f ${NAME} ${BONUS_NAME}

re: fclean all

.PHONY: all clean fclean re bonus ${OBJ_DIR}
