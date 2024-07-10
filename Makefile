NAME = philo
CC = cc 
CFLAG = -Wall -Wextra -Werror

SRC = ./main.c	\
	  ./init_prog.c	\
	  ./monitoring.c	\
	  ./philo_routine.c	\
	  ./utils.c	\
	  ./get_set_philo.c

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