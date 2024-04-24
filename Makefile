# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 13:00:13 by elilliu           #+#    #+#              #
#    Updated: 2024/04/24 18:17:42 by elilliu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipex_bonus

INCLUDE = include/pipex.h

SRC_DIR = src
BONUS_DIR = src_bonus

SRC = pipex.c children.c exec_cmd.c utils.c
BONUS_SRC = pipex_bonus.c children.c exec_cmd.c utils.c

LIBFT_DIR = libft
LIBFT_PATH = ${LIBFT_DIR}/libft.a

OBJ_DIR = objects
OBJ_BONUS_DIR = objects_bonus

OBJ = ${addprefix ${OBJ_DIR}/, ${SRC:.c=.o}}
OBJ_BONUS = ${addprefix ${OBJ_BONUS_DIR}/, ${BONUS_SRC:.c=.o}}

CC = cc
CFLAGS = -Wall -Wextra -Werror

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c ${INCLUDE}
		mkdir -p ${OBJ_DIR}
		${CC} ${CFLAGS} -c $< -o $@ -g3
		
${OBJ_BONUS_DIR}/%.o: ${BONUS_DIR}/%.c ${INCLUDE}
		mkdir -p ${OBJ_BONUS_DIR}
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
		rm -rf ${OBJ_DIR} ${OBJ_BONUS_DIR}

fclean: clean;
		${MAKE} -C ${LIBFT_DIR} fclean
		rm -f ${NAME} ${BONUS_NAME}

re: fclean all

.PHONY: all clean fclean re bonus ${OBJ_DIR}
