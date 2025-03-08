TARGET_PROGRAM		= philo

CMD					= cc

INCLUDES			= includes

CFLAGS				= -Werror -Wall -Wextra -I$(INCLUDES) -g

SRCS_PROGRAM		= \
						srcs/main.c\
						srcs/ft_atol.c\
						srcs/ft_help.c\
						srcs/ft_utils.c\
						srcs/ft_init.c\

OBJS_PROGRAM		= $(SRCS_PROGRAM:.c=.o)

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
