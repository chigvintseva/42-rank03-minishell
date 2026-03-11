# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/13 19:20:27 by achigvin          #+#    #+#              #
#    Updated: 2025/11/16 23:57:01 by achigvin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

# sources
SRC_LIBFT = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
            ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
            ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
            ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
            ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c \
            ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
            ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_atol.c

SRC_PRINTF = ft_printf/ft_printf.c ft_printf/ft_charinput.c \
             ft_printf/ft_strinput.c ft_printf/ft_intinput.c \
             ft_printf/ft_ptrinput.c ft_printf/ft_nbrbase.c \
             ft_printf/ft_ltoa.c ft_printf/ft_printf_styled.c \
             ft_printf/colours.c

SRC_GNL = gnl/get_next_line.c \
			gnl/get_next_line_utils.c

SRC = $(SRC_LIBFT) $(SRC_PRINTF) $(SRC_GNL)

OBJ_DIR = objects
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $?

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/ft_printf
	mkdir -p $(OBJ_DIR)/gnl

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re

-include $(DEP)