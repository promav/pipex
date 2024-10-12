CC = gcc
CFLAGS = -Wall -Werror -Wextra -Iinclude -Ilibft/libs
SRC = src/principals.c src/aux.c src/aux2.c src/aux3.c
OBJ = $(SRC:src/%.c=obj/%.o)
NAME = pipex
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)/libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

obj:
	@mkdir -p obj

$(NAME): obj $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "$(NAME) compiled successfully"

$(OBJ): obj/%.o: src/%.c | obj
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf obj
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "make clean done"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "make fclean done"

re: fclean all

.PHONY: all clean fclean re


