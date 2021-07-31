SRC = init.c \
      life.c \
      main.c \
      utils.c \

OBJ = ${SRC:.c=.o}

NAME = philo

HEAD = philo.h

RM = rm -f

CC = gcc

%.o: %.c
		$(CC) -Wall -Wextra -Werror -g -c $< -o $@

$(NAME): $(OBJ) $(HEAD)
		 $(CC) $(OBJ) -o ${NAME} -lpthread

all:	 ${NAME}

clean:
		 ${RM} ${OBJ}

fclean:	 clean
		 ${RM} ${NAME}

re:		 fclean all

.PHONY:	 all clean fclean re