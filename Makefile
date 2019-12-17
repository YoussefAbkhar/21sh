# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/16 19:55:13 by yabakhar          #+#    #+#              #
#    Updated: 2019/11/06 19:00:14 by yabakhar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

CFLAGS = -g -Wall -Werror -Wextra

SRCS = main.c

LIBFT = libft/libft.a

CC = gcc

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):$(OBJ)
	@make -C libft
	@$(CC) -g $(CFLAGS) $(OBJ) $(LIBFT) -ltermcap -o $(NAME)
	@echo "\033[32m$(NAME) created\n\033[0m"

clean:
	@make clean -C libft
	@rm -f $(OBJ)
	@echo "\033[31mFiles .o deleted\n\033[0m"

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "\033[31mBinary $(NAME) deleted\n\033[0m"

re: fclean all
