NAME = philo

CC = clang
CFLAGS = -Wall -Wextra -Werror -pthread -g3

SRCS = \
	philo.c \
	parsing.c \
	init.c \
	utils.c \
	simulation.c \
	monitor.c \
	cleanup.c

OBJS = $(SRCS:.c=.o)

### règle principale
all: $(NAME)

### build final
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

### compilation .c -> .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

### nettoyage
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re