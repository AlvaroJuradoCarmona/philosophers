# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajurado- <ajurado-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 13:22:25 by ajurado-          #+#    #+#              #
#    Updated: 2024/02/01 13:23:07 by ajurado-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= philo
CFLAGS		= -Wall -Wextra -Werror -pthread -g
SRCS		= philosophers.c check_args.c control.c free.c routine.c
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