CC = gcc
RM = rm -rf
NAME = ex3
RULES = all clean fclean dbg re

SRCS = $(addprefix srcs/, \
				print.c \
				)

OBJS = $(SRCS:.c=.o)

CFLAGS = -W -Wall -Werror -Wextra -Wpedantic
CFLAGS += -I ./incs

LDFLAGS = -L . -larithmetic

D_LIB = lib
LIBNAME = libarithmetic
LIB = $(LIBNAME).a

all: $(LIB) $(NAME)

$(LIB):
	$(MAKE) -C lib

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(D_LIB) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIB)
	$(RM) incs/$(LIBNAME)
	$(MAKE) -C $(D_LIB) fclean

re: fclean all
	$(MAKE) -C $(D_LIB) re

help:
	echo "Available rules : $(NAME) $(RULES)"

.NOTPARALLEL: fclean clean

.PHONY: $(RULES)
