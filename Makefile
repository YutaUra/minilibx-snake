# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yura <yura@student.42tokyo.jp>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/13 19:46:15 by yura              #+#    #+#              #
#    Updated: 2020/11/23 18:57:28 by yura             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := snake.a
MINILIBX := libmlx.dylib
SRCS := game.c math.c place.c snake.c
OBJS := ${SRCS:%.c=%.o}
CC := gcc
CFLAGS := -Wall -Wextra -Werror

all: $(NAME)

$(NAME): ${MINILIBX} ${OBJS}
	gcc -fsanitize=address ${MINILIBX} ${OBJS} main.c -o ${NAME}


$(MINILIBX):
	$(MAKE) -C ./minilibx
	cp ./minilibx/${MINILIBX} ./

clean:
	$(MAKE) -C ./minilibx clean
	rm -f ${OBJS}


fclean: clean
	rm -f ${NAME} ${MINILIBX}

re: fclean $(NAME)
	

bonus:

.PHONY: clean fclean all re bonus