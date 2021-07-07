# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zdawnsta <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/28 17:49:25 by zdawnsta          #+#    #+#              #
#    Updated: 2020/09/29 12:28:22 by zdawnsta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS = src/check_param.c src/cub3d.c src/drawing.c src/gnl.c \
	src/help_functions.c src/image.c src/libft.c src/operations.c \
	src/parsing.c src/start_position.c src/screenshot.c src/set_param.c \
	src/sprites.c

HEADER = cub3d.h
OBJS = $(SRCS:.c=.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror
MLX = libmlx.dylib
LXFLAGS = -lmlx -framework OpenGL -framework AppKit
RM = rm -f
RMR = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\n\033[0;33mCompiling..."
	$(CC) -o $(NAME) -L $(MLX) $(LXFLAGS) $(OBJS)
	@echo "\033[0m"

clean:
	@echo "\033[0;31mCleaning..."
	$(RMR) $(OBJS)
	$(RM) screenshot.bmp
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mRemoving executable..."
	$(RM) $(NAME)
	@echo "\033[0m"

re: fclean all

.PHONY: all clean fclean re
