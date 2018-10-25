CC = gcc
RM = rm -rf
NAME = ex1
RULES = all clean fclean dbg re

SRCS = arithmetic.c \
			 print.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -W -Wall -Werror -Wextra -Wpedantic

LDFLAGS = -lm

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

help:
	echo "Available rules : $(NAME) $(RULES)"

.PHONY: $(RULES)
