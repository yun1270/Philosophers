NAME = philo

CC = gcc

CFLAGS = -Werror -Wall -Wextra -lpthread

RM = rm -rf

SRCS =	main.c\
		print_message.c\
		run_philo.c\
		start_philo.c\
		struct.c\
		utils.c

$(NAME) :
	gcc $(CFLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(NAME)

re : fclean all

.PHONY:		all clean fclean re
