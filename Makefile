# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: belhatho <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/01 01:27:34 by belhatho          #+#    #+#              #
#    Updated: 2020/12/01 01:27:37 by belhatho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

SRCS = main.c ft_vec.c ft_ray.c ft_cam.c ft_hook.c
SRCS += ft_parse.c ft_parse1.c ft_parse2.c ft_cleanup.c
SRCS += ft_rotate.c	ft_draw.c ft_init.c ft_lighting.c
SRCS += ft_hit.c ft_hit_objs.c

SRC = $(SRCS:%=srcs/%)

HEADER = headers
OBJ_DIR = objs

OBJ = $(SRCS:%.c=objs/%.o)

OK_COLOR=\x1b[32;01m
NO_COLOR=\x1b[0m
BUILD_PRINT = $(OK_COLOR)rtv1 successfully compiles$(NO_COLOR)
OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)

ifeq ($(shell uname), Darwin)
$(info MacOs detected)
MLX = -lmlx -framework OpenGL -framework AppKit
else
$(info $(shell uname) detected)
MLX = -lm -lmlx -lXext -lX11
endif

#CFLAGS = -Wall -Wextra -Werror
LIBFT = ./libft/ -lft
THREAD = -lpthread
MYFLAG =  $(MLX)  $(THREAD) -L $(LIBFT)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@gcc $(CFLAGS) -o $(NAME) $^ $(MYFLAG)
	@echo "$(BUILD_PRINT)"

$(OBJ_DIR):
	mkdir -p $@

objs/%.o: srcs/%.c headers/rtv1.h | $(OBJ_DIR)
	@echo "`gcc $(CFLAGS) -o $@ -c $< -I headers -I libft`$< => $@ $(OK_STRING)"

clean:
	@echo "$(OK_COLOR)Deleting objects...$(NO_COLOR)"
	@rm -rf $(OBJ)
	@make clean -C libft

fclean: clean
	@echo "$(OK_COLOR)Deleting rtv1...$(NO_COLOR)"
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
