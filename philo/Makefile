NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c arg_check.c init.c utils.c routine.c life_cycle.c monitoring.c
OBJS = $(SRCS:.c=.o)

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME)
	@echo Done!

clean:
	@rm -f $(OBJS)
	@echo Cleaned!

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
