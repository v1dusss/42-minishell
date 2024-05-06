Name = minishell

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes -I libft
LIBFT	:=	libft
LDFLAGS	:=	-lreadline

VPATH = \
	src

# Sources
SRC = \
	main.c 

# Objects
OBJ_DIR := obj
OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Rules
all: libft $(Name)

$(Name): $(OBJ)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) -o $(Name) $(OBJ) $(LDFLAGS) $(LIBFT)/libft.a

clean:
	rm -rf $(OBJ_DIR)
	make -C libft clean

fclean: clean
	rm -f $(Name)
	make -C libft fclean

re: fclean all

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@