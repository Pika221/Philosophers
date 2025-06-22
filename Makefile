NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror 
SRCS = arg_check.c init.c life_circle.c main.c monitoring.c routine.c utils.c
OBJS = $(SRCS:.c=.o)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

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
