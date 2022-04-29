# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 09:10:14 by Loui :)           #+#    #+#              #
#    Updated: 2022/04/29 13:57:30 by Loui :)          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -pthread -ggdb3 ##This one fucks up my execution :) -fsanitize=thread

SRC			=	main.c input_error.c print.c utils1.c #main.c utils1.c 

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