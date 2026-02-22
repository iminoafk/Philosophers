NAME = philo

CC = clang
CFLAGS = -Wall -Wextra -Werror -g3

SRCS = \
	philo.c \
	parsing.c \

OBJS = $(SRCS:.c=.o)

### règle principale
all: $(NAME)

### build final
$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

### compilation .c -> .o
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

### nettoyage
clean:
	rm -f $(OBJS)
	$(MAKE) -C clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C fclean

re: fclean all

.PHONY: all clean fclean re