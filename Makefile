NAME = philo
CC = gcc 
CFLAG = -Wall -Wextra -Werror  -fsanitize=thread

SRC = main.c	\
	  philo_routine.c \
	  get_set_philo.c \
	  monitor.c \
	  utils.c	\
	  struct_philo.c

OBJ = $(SRC:.c=.o)

all:$(NAME)

%.o:%.c philo.h
	$(CC) $(CFLAG) -c $< -o $@

$(NAME):$(OBJ)
	$(CC) $(CFLAG) $(OBJ) -o $(NAME)

clean :
	rm -f $(OBJ)
fclean : clean
	rm -f $(NAME)

re : fclean all