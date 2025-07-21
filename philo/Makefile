GREEN	=	\033[1;32m
CYAN	=	\033[0;36m
WHITE	=	\033[0m
CLEAR	=	\r\033[K

NAME = philo


CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -I inc

SRCS = 	src/main.c	\


OBJS = $(SRCS:%.c=objs/%.o)

all: $(NAME)

$(NAME): objs $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)philo ready$(WHITE)"


objs:
	@mkdir -p objs/src/

objs/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf objs
	@echo "Objetcs files deleted."

fclean: clean
	@rm -f $(NAME)
	@echo "Full clean completed"

re: fclean all

.PHONY: all clean fclean re
