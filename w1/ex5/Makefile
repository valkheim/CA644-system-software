CC = gcc
RM = rm -rf
NAME = ex5
RULES = all clean fclean dbg re

D_SRCS = src
D_OBJS = obj
D_INCS = inc

SRCS = $(addprefix $(D_SRCS)/, \
	ex5.c \
	get_next_line.c \
	utils.c \
	)

OBJS = $(SRCS:$(D_SRCS)/%.c=$(D_OBJS)/%.o)

INC = -I $(D_INCS)

CFLAGS = -W -Wall -Werror -Wextra -Wpedantic -std=c89
CFLAGS += $(INC)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LDFLAGS)

$(D_OBJS)/%.o: $(D_SRCS)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	find -name "*~" -delete -o -name "#*#" -delete
	$(RM) $(D_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

dbg: CFLAGS += -g3 -O0 -DDEBUG
dbg: re

postnazi: CC := clang -Weverything
postnazi: re

nazi:
	$(MAKE) postnazi

help:
	echo "Available rules : $(NAME) $(RULES)"

.PHONY: $(RULES)
