CC = gcc
CFFLAGS = -Wall -Werror -Wextra
SRC = ft_memcpy.c ft_strdup.c ft_strlcat.c ft_substr.c ft_split.c ft_strjoin.c ft_strlen.c ft_printf.c ft_putchar.c ft_puthexa.c ft_putnbr.c ft_putstr.c ft_putunbr.c ft_putvoid.c principals.c aux.c
OBJ = $(SRC:.c=.o)
LIBS = libft.h ft_printf.h
NAME = pipex

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $(LIB) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
