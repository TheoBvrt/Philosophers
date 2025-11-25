NAME = philo

SRCS =	./srcs/main.c \
		./srcs/init.c \
		./srcs/exit.c \
		./srcs/philo.c \
		./srcs/monitoring.c \

OBJS = ${SRCS:.c=.o}
CC = gcc
RM = rm -f
CFLAGS = -Iheaders -lpthread -g

all : ${NAME}

%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME} : ${OBJS}
	${MAKE} -C ./libft
	$(CC) $(OBJS) ./libft/libft.a -o $(NAME)

clean:
	${RM} ${OBJS}
	make clean -C ./libft

fclean: clean
	${RM} ${NAME}
	make fclean -C ./libft

re: fclean all