NAME		=	philo
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -pthread ##These two fuck up my compilation :) -fsanitize=thread -ggdb3 

SRC			=	main.c utils1.c input_error.c

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