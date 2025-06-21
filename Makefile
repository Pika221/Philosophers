NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = arg_check.c init.c life_circle.c main.c utils.c monitoring.c routine.c 
OBJS = $(SRCS: .c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re