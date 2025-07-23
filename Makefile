NAME = philo
CC = cc
CFLAGS = -g -pthread
# -Werror -Wextra -Wall -g

SRCS = main.c check_args_utils.c utils.c init_philo.c clean_up.c \
		philos.c routine.c\

OBJS = $(SRCS:.c=.o)


do: all clean

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
