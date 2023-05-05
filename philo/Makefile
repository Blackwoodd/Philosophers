NAME	= philo

SRCS	= src/main.c src/time.c src/mutex.c src/init_arg.c src/philo_eat.c src/print.c

OBJS	= $(SRCS:.c=.o)
RM		= rm -f
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -fsanitize=thread

all		: $(NAME)

$(NAME)	: $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean	:
			$(RM) $(OBJS)

fclean	: clean
			$(RM) $(NAME)

re		:		fclean all

.PHONY	:		all clean fclean re