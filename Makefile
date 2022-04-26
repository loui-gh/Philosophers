NAME		=	philo
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -ggdb3 -pthread -fsanitize=thread

SRC			=	main.c utils1.c utils2.c ft_atoi.c

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