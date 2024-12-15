# * ft_printf Makefile *

# Project name
NAME = libftprintf.a

# Compiling flags
CFLAGS = -Wall -Wextra -Werror

# Source files
LIB_SRCS = ft_printf.c \
	arg_hex.c \
	arg_int.c \
	arg_others.c \
	formatinfo.c \
	formatinfo_parse.c \
	utils_bonus.c

# Bonus source files
LIB_SRCS_BONUS = ft_printf_bonus.c \
	arg_hex_bonus.c \
	arg_int_bonus.c \
	arg_others_bonus.c \
	formatinfo_bonus.c \
	formatinfo_parse_bonus.c \
	utils_bonus.c

# Object files
LIB_OBJS = $(LIB_SRCS:.c=.o)

# Bonus object files
LIB_OBJS_BONUS = $(LIB_SRCS_BONUS:.c=.o)

# Archives
AR = ar rcs 

# Colors
RED	= "\033[0;31m"
GREEN = "\033[0;32m"
NO_COLOR = "\033[0m"

# Rules
all:$(NAME)

$(NAME):$(LIB_OBJS)
	@echo $(GREEN)Making $(NAME) and .o files$(NO_COLOR)
	$(AR) $(NAME) $(LIB_OBJS)

%.o:%.c
	@echo "$@"
	cc $(CFLAGS) -o $@ -c $<

bonus:$(LIB_OBJS_BONUS)
	@echo $(GREEN)Making $(NAME) and .o files [Bonus] $(NO_COLOR)
	$(AR) $(NAME) $(LIB_OBJS_BONUS)

clean:
	@echo $(RED)Removing .o files$(NO_COLOR)
	rm -rf ${LIB_OBJS} $(LIB_OBJS_BONUS)

fclean: clean
	@echo $(RED)Removing $(NAME) $(NO_COLOR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
