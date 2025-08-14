NAME = philo
CC = cc
CFLAGS = -Werror -Wextra -Wall

SRCS = main.c check_args_utils.c utils.c init_infos.c philos.c exit_philo.c routine.c clean_up.c\

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
