CC = gcc
AR = ar
CFLAGS = -Wall -Wextra -Werror -pedantic -Wno-deprecated-declarations -I.
NAME = libhblk_crypto.a

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
    $(AR) rcs $@ $^

%.o: %.c hblk_crypto.h
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJ)

fclean: clean
    rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re