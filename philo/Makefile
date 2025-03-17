TARGET_PROGRAM		= philo

CMD					= cc

INCLUDES			= includes

CFLAGS				= -Werror -Wall -Wextra -g -I$(INCLUDES) -pthread #-fsanitize=thread

SRCS_PROGRAM		= \
	srcs/ft_atol.c\
	srcs/ft_exit.c\
	srcs/ft_help.c\
	srcs/ft_init.c\
	srcs/ft_input.c\
	srcs/ft_routine.c\
	srcs/ft_utils.c\
	srcs/main.c\

OBJS_PROGRAM		= $(SRCS_PROGRAM:.c=.o)

TSAN_OPTIONS		= second_deadlock_stack=1

all : $(TARGET_PROGRAM)

$(TARGET_PROGRAM) : $(OBJS_PROGRAM)
	$(CMD) $(CFLAGS) -o $@ $^

%.o : %.c
	$(CMD) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_PROGRAM)

fclean: clean
	rm -rf $(TARGET_PROGRAM)

re : fclean all

.PHONY : all clean fclean re
