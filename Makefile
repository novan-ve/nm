NAME = ft_nm

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

SRC = main.c \
		handler.c \
		parse_32.c \
		parse_64.c \
		symbol.c \
		symbol_type_32.c \
		symbol_type_64.c

HEADER = nm.h

LIBFT = libft/libft.a

OBJ := $(SRC:%.c=./$(OBJ_DIR)/%.o)
SRC := $(SRC:%=./$(SRC_DIR)/%)

HEADER := $(HEADER:%=./$(INC_DIR)/%)

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(FLAGS) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME): $(OBJ)
	$(MAKE) -s -C libft
	$(CC) $^ -o $@ $(LIBFT)

$(OBJ_DIR):
	mkdir -p $@

clean:
	$(RM) $(OBJ)
	$(MAKE) -C libft clean

fclean:
	$(RM) $(OBJ) $(NAME)
	$(MAKE) -C libft fclean

re: fclean
	$(MAKE)
