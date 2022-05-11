# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 09:10:14 by Loui :)           #+#    #+#              #
#    Updated: 2022/05/10 23:59:04 by Loui :)          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -pthread -ggdb3 -fsanitize=thread

SRC			=	main.c utils.c input_error.c cutlery.c \
				eat_sleep_shit_etc.c time.c death.c \
				init_structs_create_threads.c

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