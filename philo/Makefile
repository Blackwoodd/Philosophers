############## NAME #############

NAME	= philo



############# SOURCES ###########

SRCS	=	src/main.c \
		src/time.c \
		src/mutex.c \
		src/init_arg.c \
		src/philo_eat.c \
		src/print.c \
		src/death.c	



########## VARIABLES ############

OBJS		= $(SRCS:.c=.o)
RM		= @rm -f
CC		= @cc
CFLAGS		= -Wall -Wextra -Werror -fsanitize=thread


########### REGLES ##############

all	:	$(NAME)


$(NAME)	:	$(OBJS)
			@echo "\033[0;31;5m   ___ _     _ _                       _               \033[0m"
			@echo "\033[0;31;5m  / _ \ |__ (_) | ___  ___  ___  _ __ | |__   ___ _ __ \033[0m"
			@echo "\033[0;31;5m / /_)/ '_ \| | |/ _ \/ __|/ _ \| '_ \| '_ \ / _ \ '__|\033[0m"
			@echo "\033[0;31;5m/ ___/| | | | | | (_) \__ \ (_) | |_) | | | |  __/ |   \033[0m"
			@echo "\033[0;31;5m\/    |_| |_|_|_|\___/|___/\___/| .__/|_| |_|\___|_|   \033[0m"
			@echo "\033[0;31;5m                                |_|                    \033[0m"
			@echo "\033[0;33mCompilation...\033[0m"
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			@echo "\033[0;32mCompilation : OK.\033[0m"

clean	:
			@echo "\033[0;33mClean...\033[0m"
			$(RM) $(OBJS)
			@echo "\033[0;32mClean : OK.\033[0m"

fclean	:	clean
			$(RM) $(NAME)

re	:		fclean all

.PHONY	:		all clean fclean re
