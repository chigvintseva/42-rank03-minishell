# Test Makefile for Parser

NAME = test_parser

LIBFT_DIR = ../include/libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I../include -I$(LIBFT_DIR) -g

SRC_DIR = ../src/parser
SRC = $(SRC_DIR)/ast_builder.c \
	  $(SRC_DIR)/cmd_builder.c \
	  $(SRC_DIR)/cmd_builder_utils.c \
	  $(SRC_DIR)/cmd_argv.c \
	  $(SRC_DIR)/create_new.c \
	  $(SRC_DIR)/free_functions.c \
	  $(SRC_DIR)/parser.c \
	  $(SRC_DIR)/syntax_rules.c \
	  $(SRC_DIR)/utils.c \
	  test_parser.c

OBJ_DIR = obj
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRC)))

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) re

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: ../src/parser/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/test_parser.o: test_parser.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

test: all
	./$(NAME)

leaks: all
	@echo "Running with leaks detection..."
	leaks --atExit -- ./$(NAME) "ls -la | grep test" 2>/dev/null | grep -E "(leaks|total|Process)" || echo "No leaks detected"

.PHONY: all clean fclean re test valgrind