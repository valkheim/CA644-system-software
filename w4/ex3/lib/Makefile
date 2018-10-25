DEBUG	= yes
DETAILS	= no
CC	= gcc
RM	= rm -f

CFLAGS = -W -Wall -Werror -Wextra -Wpedantic
CFLAGS	+= -I incs/

ifeq ($(DEBUG),yes)
	CFLAGS	+= -g
endif

LDFLAGS	+=

NAME	=arithmetic
LIBNAME = $(NAME).a

OBJDIR = obj

SRCS	= srcs/arithmetic.c

OBJS	= $(SRCS:srcs/%.c=$(OBJDIR)/%.o)

all:	$(LIBNAME)

$(LIBNAME):	$(OBJS)
	@mkdir -p lib
	@ar rc lib/$(LIBNAME) $(OBJS)
	@ranlib lib/$(LIBNAME)
	@cp lib/$(LIBNAME) ../lib$(LIBNAME)
	@mkdir -p ../incs && mkdir -p ../incs/lib$(NAME) \
	&& cp incs/lib$(NAME)/arithmetic.h ../incs/lib$(NAME)/
	@echo "$(LIBNAME) compiled in debug mode."

$(OBJDIR)/%.o:	srcs/%.c
	@mkdir -p $(dir $@)
ifeq ($(DETAILS),yes)
	$(CC) $(CFLAGS) -c $< -o $@
else
	@echo -e "Compile:\t$<"
	@$(CC) $(CFLAGS) -c $< -o $@
endif

.NOTPARALLEL: fclean clean

.PHONY: clean fclean re

clean:
	@echo "Cleaning $(NAME) object files ..."
	@$(RM) $(OBJS)
	@$(RM) -r obj/

fclean:	clean
	@echo "Cleaning $(NAME) files ..."
	@$(RM) lib/$(LIBNAME)
	@$(RM) ../$(LIBNAME)

re:	fclean all
