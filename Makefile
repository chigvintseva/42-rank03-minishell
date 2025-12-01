# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achigvin <achigvin@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/01 20:45:35 by achigvin          #+#    #+#              #
#    Updated: 2025/12/01 20:45:35 by achigvin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_DIR = include/libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR)

# ---------
SRC_DIR = src
SRC = $(SRC_DIR)/main.c \
		

# ------------creating objects---
OBJ_DIR = $(SRC_DIR)/obj
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


# -------- name rule --------
all: $(LIBFT) $(NAME)


# --------- main compilation-----------
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(MLXFLAGS) $(LIBFT) -o $(NAME)


# ------ libft compilation, -C flag is for "change directory to the subdirectory libft"
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# --------------objects compilation ---
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


# --------- clean fclean re rules-----------
clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(OBJ_DIR)

re: fclean all


# -------------------
.PHONY: all clean fclean re
