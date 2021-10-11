NAME = philo_bonus

HEADER = philosophers_bonus.h

SRC = philosophers.c threads/life_philosophers.c threads/threads_starting.c \
	threads/threads.c utils/ft_split.c utils/ft_substr.c utils/pars_args.c \
	utils/utils.c utils/utils2.c utils/utils3.c utils/validate.c 

FLAGS = -Wall -Wextra -Werror

OBJ = ${SRC:.c=.o}

all : ${NAME}

%.o : %.c $(HEADER)
	gcc ${FLAGS} -c $< -o $@

${NAME} : ${SRC} ${OBJ}
	gcc ${FLAGS} -o ${NAME} ${SRC}

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re