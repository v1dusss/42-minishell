Name = minishell

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = -I includes -I libft
LIBFT	:=	libft
LDFLAGS	:=	-lreadline

VPATH = \
	src \
	src/token

# Sources
SRC = \
	main.c \
	tokenizer.c \
	abstract_syntax_tree.c \
	ft_lst_utils.c

# Objects
OBJ_DIR := obj
OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Rules
all: libft $(Name)

$(Name): $(OBJ)
	@make -C $(LIBFT)
	@$(CC) $(CFLAGS) $(INC) -o $(Name) $(OBJ) $(LDFLAGS) $(LIBFT)/libft.a
	@echo "\033[1;32m ✅ [minishell created]\033[0m"

clean:
	@rm -rf $(OBJ_DIR)
	@make -C libft clean

fclean:
	@echo "\033[1;33m 🗑️  Deleting the obj directory and executable... 🗑️\033[0m"
	@make clean
	@rm -f $(Name)
	@echo "\033[0;37m 🧹 [minishell deleted]\033[0m"
	@make -C libft fclean

re: fclean all

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@