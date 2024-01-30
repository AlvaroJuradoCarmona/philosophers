NAME 		= philo
CFLAGS		= -Wall -Wextra -Werror -g
SRCS		= philosophers.c check_args.c control.c initialize.c \
		free.c routine.c
OBJS		= $(SRCS:.c=.o)
RM			= rm -rf

all: $(NAME)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	gcc $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re