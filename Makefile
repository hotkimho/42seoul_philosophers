NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror
# CFLAGS += -g3 -fsanitize=address
AR = ar rcs
RM = rm -f


FUNC =	main.c\
		error.c\
		parse.c\
		init_philo.c\
		philo_util.c\
		philo_thread.c\
		print.c

SRCS = $(addprefix src/, $(FUNC))
OBJS = $(SRCS:c=o)


$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $^

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re: fclean all

.PHONY : bonus all clean fclean re