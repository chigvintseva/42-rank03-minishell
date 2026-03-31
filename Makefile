# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aleksandra <aleksandra@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/01 20:45:35 by achigvin          #+#    #+#              #
#    Updated: 2026/03/31 18:24:38 by aleksandra       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_DIR = include/libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR) -I./include
LDFLAGS = -lreadline

# Colors for output
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RED = \033[0;31m
NC = \033[0m

# ---------
SRC_DIR = src
SRC = $(SRC_DIR)/main.c \
	$(SRC_DIR)/minishell.c \
	$(SRC_DIR)/shell_init_free.c \
	$(SRC_DIR)/error_case.c \
	$(SRC_DIR)/heredoc_utils.c \
	$(SRC_DIR)/lexer/lexer.c \
	$(SRC_DIR)/lexer/hadle_words_syntax.c \
	$(SRC_DIR)/lexer/lexing_utils.c \
	$(SRC_DIR)/lexer/list_utils.c \
	$(SRC_DIR)/parser/parser.c \
	$(SRC_DIR)/parser/ast_builder.c \
	$(SRC_DIR)/parser/cmd_builder.c \
	$(SRC_DIR)/parser/cmd_builder_utils.c \
	$(SRC_DIR)/parser/cmd_argv.c \
	$(SRC_DIR)/parser/create_new.c \
	$(SRC_DIR)/parser/free_functions.c \
	$(SRC_DIR)/parser/syntax_rules.c \
	$(SRC_DIR)/parser/utils.c \
	$(SRC_DIR)/runner/runner.c \
	$(SRC_DIR)/runner/pipe.c \
	$(SRC_DIR)/runner/exec_cmd.c \
	$(SRC_DIR)/runner/external.c \
	$(SRC_DIR)/runner/redir.c \
	$(SRC_DIR)/runner/builtins/echo.c \
	$(SRC_DIR)/runner/builtins/cd.c \
	$(SRC_DIR)/runner/builtins/pwd.c \
	$(SRC_DIR)/runner/builtins/env.c \
	$(SRC_DIR)/runner/builtins/export.c \
	$(SRC_DIR)/runner/builtins/unset.c \
	$(SRC_DIR)/runner/builtins/exit.c \

# Creating objects
OBJ_DIR = $(SRC_DIR)/obj
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


# -------- Main Build Rules --------
all: $(LIBFT) $(NAME)
	@echo "$(GREEN)✓ minishell compiled successfully$(NC)"

# Compile main executable
$(NAME): $(OBJ) $(LIBFT)
	@echo "$(BLUE)Linking minishell...$(NC)"
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)

# Compile libft library
$(LIBFT):
	@echo "$(BLUE)Building libft...$(NC)"
	$(MAKE) -C $(LIBFT_DIR)

# Create object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/lexer
	mkdir -p $(OBJ_DIR)/parser
	mkdir -p $(OBJ_DIR)/runner
	mkdir -p $(OBJ_DIR)/runner/builtins

# Compile source files to objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@


# --------- Clean Rules ---------
clean:
	@echo "$(YELLOW)Cleaning object files...$(NC)"
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(YELLOW)Removing executable...$(NC)"
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(OBJ_DIR)

re: fclean all


# --------- Testing Rules ---------
test: all
	@echo "$(GREEN)Build successful! Ready for testing.$(NC)"
	@echo "$(BLUE)Run minishell with: ./$(NAME)$(NC)"

# Run with valgrind (memory leak detection)
valgrind: all
	@echo "$(BLUE)Running with valgrind...$(NC)"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

# Run with valgrind (summary only - faster)
valgrind-quick: all
	@echo "$(BLUE)Running with valgrind (quick mode)...$(NC)"
	valgrind --leak-check=summary ./$(NAME)

# Run with detailed valgrind output
valgrind-verbose: all
	@echo "$(BLUE)Running with valgrind (verbose)...$(NC)"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(NAME)

# Help message
help:
	@echo "$(BLUE)Minishell Makefile - Available targets:$(NC)"
	@echo "  $(GREEN)make$(NC) or $(GREEN)make all$(NC)     - Compile minishell"
	@echo "  $(GREEN)make test$(NC)             - Build and show ready message"
	@echo "  $(GREEN)make valgrind$(NC)         - Run with full valgrind checks"
	@echo "  $(GREEN)make valgrind-quick$(NC)   - Run with valgrind (leak summary only)"
	@echo "  $(GREEN)make valgrind-verbose$(NC) - Run with detailed valgrind output"
	@echo "  $(GREEN)make clean$(NC)            - Remove object files"
	@echo "  $(GREEN)make fclean$(NC)           - Remove executable and object files"
	@echo "  $(GREEN)make re$(NC)               - Rebuild everything"
	@echo "  $(GREEN)make help$(NC)             - Show this message"


# -------------------
.PHONY: all test valgrind valgrind-quick valgrind-verbose clean fclean re help
