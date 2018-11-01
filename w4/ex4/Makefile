CC = gcc
RM = rm -rf
NAME = ex1
RULES = all clean fclean dbg re lib

SRCS = print.c

LIB_SRC = arithmetic.c
LIB = libArithmetic.so

OBJS = $(SRCS:.c=.o)

CFLAGS = -W -Wall -Werror -Wextra -Wpedantic

LDFLAGS = -lm

all: $(NAME)

lib:
	$(CC) -shared -o $(LIB) -fPIC $(LIB_SRC)

$(NAME): lib $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LDFLAGS) -L. -lArithmetic

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(LIB)

re: fclean all

run:
	LD_LIBRARY_PATH=. ./$(NAME)

help:
	echo "Available rules : $(NAME) $(RULES)"

.PHONY: $(RULES)
