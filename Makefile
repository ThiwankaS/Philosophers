NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -std=c99 -D_DEFAULT_SOURCE -pthread -Iincludes

CFLAGS_DEBUG_TSAN = -Wall -Wextra -Werror -std=c99 -D_DEFAULT_SOURCE -g -fsanitize=thread -pthread -Iincludes

CFLAGS_DEBUG_ASAN = -Wall -Wextra -Werror -std=c99 -D_DEFAULT_SOURCE -g -fsanitize=address -pthread -Iincludes

CFLAGS_VALGRIND = -Wall -Wextra -Werror -std=c99 -D_DEFAULT_SOURCE -g -O1 -pthread -Iincludes

SRCS = \
	args.c \
	main.c \
	philosopher.c \
	simulation.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

debug_leaks: $(OBJS)
	$(CC) $(CFLAGS_DEBUG_ASAN) $(OBJS) -o $(NAME)

debug_drc: $(OBJS)
	$(CC) $(CFLAGS_DEBUG_TSAN) $(OBJS) -o $(NAME)

debug_valgrind: $(OBJS)
	$(CC) $(CFLAGS_VALGRIND) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug_leaks debug_drc debug_valgrind
