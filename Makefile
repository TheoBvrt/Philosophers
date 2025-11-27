NAME = philo

SRCS =	./srcs/main.c \
		./srcs/init.c \
		./srcs/philo.c \
		./srcs/monitoring.c \
		./srcs/time.c \
		./srcs/utils.c

OBJS = ${SRCS:.c=.o}
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -Iheaders -lpthread -g

all : ${NAME}

%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME} : ${OBJS}
	$(CC) $(OBJS) -o $(NAME)

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY:	all clean fclean re