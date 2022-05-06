# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 09:10:14 by Loui :)           #+#    #+#              #
#    Updated: 2022/05/06 12:06:26 by Loui :)          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -pthread -ggdb3 -fsanitize=thread ##This one fucks up my execution :) 

SRC			=	main.c utils.c init_structs.c input_error.c \
				take_up_forks.c eat_sleep_shit_etc.c time.c \
				free.c

OBJ			=	${SRC:.c=.o}

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lpthread -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re