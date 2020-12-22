# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: belhatho <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 02:41:26 by belhatho          #+#    #+#              #
#    Updated: 2019/11/30 16:33:56 by belhatho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC =	ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_lstdelone.c
SRC +=	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstdel.c
SRC +=	ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_lstadd.c
SRC +=	ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_strrchr.c
SRC +=	ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c 
SRC +=	ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_lstmap.c
SRC +=	ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_lstnew.c
SRC +=	ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c
SRC +=	ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c
SRC +=	ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c
SRC +=	ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c
SRC +=	ft_strnstr.c ft_strrchr.c  ft_strsplit.c ft_lstiter.c
SRC +=	ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c
SRC +=	ft_toupper.c ft_strlowcase.c ft_strcapitalize.c
SRC +=  ft_swap.c ft_strrev.c ft_str_is_alpha.c ft_str_is_numeric.c
SRC +=  ft_str_is_printable.c ft_str_is_uppercase.c ft_str_is_lowercase.c
SRC +=  ft_nbr_size.c ft_word_size.c ft_nbr_words.c ft_atoi.c get_next_line.c


OBJ = $(SRC:.c=.o)

OK_COLOR=\x1b[32;01m
NO_COLOR=\x1b[0m

BUILD_PRINT = libft.a successfully compiles
OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)
	

$(NAME): $(OBJ)
	@ar rc $(NAME) $^
	@echo "$(BUILD_PRINT)"

%.o: %.c libft.h
	@echo "`gcc $(CFLAGS) -o $@ -c $< -I .`$< => $@ $(OK_STRING)"

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
